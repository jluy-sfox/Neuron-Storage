# Deeply Human

## Simple Linux Character Driver
A collaborative repository for the development of a simple Linux character driver

### Preliminaries

• To ensure that kernel headers are properly installed in the machine, run the following commands in the terminal:

```
sudo apt update && sudo apt upgrade
sudo apt remove --purge linux-headers-*
sudo apt autoremove && sudo apt autoclean
sudo apt install linux-headers-generic
```

### Updates

• 14/02/2023: Uploaded `gpio_driver.c` and its corresponding `Makefile`. Driver successfully initializes the GPIO pins of the Rockpi N10.
• 08/02/2023: Created `Linux-Character-Driver` GitHub repository for collaborative development of a character driver.
