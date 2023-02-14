#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lendl Uy, Francis Magueflor");
MODULE_DESCRIPTION("A simple character driver for Rockpi N10");

static dev_t dev_num;
static struct class *dev_class;
static struct cdev rockpi;

#define DRIVER_NAME "simple_char_driver"
#define DRIVER_CLASS "My Module Class"

int gpio_nums[27] = {71, 72, 13, 148, 147, 146, 9, 150, 149, 
                     8, 70, 40, 39, 124, 41, 42, 64, 65, 74, 73, 
                     125, 127, 68, 66, 126, 67, 34};

// NEED TO TEST
static ssize_t driver_read(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset){
  char tmp[3] = "\n";
  
  int data, user_data;
  int data_copy = min(size, sizeof tmp);
  
  // Read value of GPIO number 71
  printk("Value of GPIO pin 0: %d\n", gpio_get_value(71));
  tmp[0] = gpio_get_value(71) + "0";
  
  user_data = copy_to_user(user_buffer, &tmp, data_copy);
  
  data = data_copy - user_data;
  
  return data;
}

// NEED TO TEST
static ssize_t driver_write(){
  
  char tmp;
  
  int data, user_data;
  int data_copy = min(size, sizeof tmp);
  
  user_data = copy_from_user(&tmp, user_buffer, data_copy);
  
  // Write value of GPIO number 71
  if (value == "0"){
    gpio_set_value(71, 0);
  } else if (value == "1"){
    gpio_set_value(71, 1);
  } else{
    printk("Invalid input!\n");
  }
  
  data = data_copy - user_data;
  
  return data;
}

static int driver_open(struct inode *inode, struct file *file){
  printk("Driver: driver_open() was called!\n");
  return 0;
}

static int driver_release(struct inode *inode, struct file *file){
  printk("Driver: driver_close() was called!\n");
  return 0;
}

static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = driver_open,
  .release = driver_release
};

static int __init DriverInit(void){
  char gpio_labels[27][10] = {"gpio-71", "gpio-72", "gpio-13", "gpio-148", "gpio-147", 
                              "gpio-146", "gpio-9", "gpio-150", "gpio-149", "gpio-8",
                              "gpio-70", "gpio-40", "gpio-39", "gpio-124", "gpio-41", 
                              "gpio-42", "gpio-64", "gpio-65", "gpio-74", "gpio-73", 
                              "gpio-125", "gpio-127", "gpio-68", "gpio-66", "gpio-126", 
                              "gpio-67", "gpio-34"};
  
  int i = 0;
  
  printk("Driver: DriverInit() was called!\n");
  
  // Allocates a device number
  if (alloc_chrdev_region(&dev_num, 0, 1, DRIVER_NAME) < 0){
    printk("Device number cannot be allocated!\n");
  }
  //printk("Device number has been successfully allocated.\n");
  
  // Creates a device class
  if ((dev_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL){
    printk("Device class cannot be created!\n");
  }
  
  if (device_create(dev_class, NULL, dev_num, NULL, DRIVER_NAME) == NULL){
    printk("Device cannot be created!\n");
  }
  
  cdev_init(&rockpi, &fops);
  
  if (cdev_add(&rockpi, dev_num, 1) == -1){
    printk("Device was not registered in the kernel!\n");
  }
  
  for (; i<27; ++i){
    if (gpio_request(gpio_nums[i], gpio_labels[i])){
      printk("GPIO %d was not allocated!\n", gpio_nums[i]);
      gpio_free(gpio_nums[i]);
      return -1;
    }
  }
  
  printk("The device has been successfully initialized!\n");
  return 0;
}

static void __exit DriverExit(void){
  
  int i = 0;
  
  printk("Driver: DriverExit() was called!\n");
  
  // Release allocated GPIO pins
  for (; i<27; ++i){
    gpio_free(gpio_nums[i]);
  }
  
  cdev_del(&rockpi);
  device_destroy(dev_class, dev_num);
  class_destroy(dev_class);
  unregister_chrdev_region(dev_num, 1);
}

module_init(DriverInit);
module_exit(DriverExit);
