#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct dp_cmd_desc {
  unsigned int *src_addr_0;
  unsigned int *src_addr_1;
  unsigned int *dst_adrr;
  unsigned short size;
  unsigned char mode;
  unsigned char dep_flag;
  unsigned char dep_ctl;
  unsigned char dep_map;
  unsigned char last_desc_flag;
  unsigned char done_irq_en;
  struct dp_cmd_desc *next;
};

int dp_request(struct dp_cmd_desc*){
  return 1;
}

int read_file(char *filename, char array[4096]){

  FILE *in;
  int i = 0;
  int j = 0;

  // Open the text file
  in = fopen(filename, "r");

  // Read the contents of the file into the array
  while(!feof(in)){
    fscanf(in, "%c", &array[i]);
    ++i;
  }

  // Close the file to avoid errors
  fclose(in);

  // Print the contents of the array
  for (; j < i-1; ++j){
    printf("%c", array[j]);
  }

  return j;

}

void write_file(char *filename, char array[4096][100], int arr_size){

  FILE *out;
  int i = 0;

  // Open an output file to write to
  out = fopen(filename, "w");
  
  // Error handling
  if (out == NULL){
    puts("Not able to create file");
    exit(0);
  }
 
  // Write contents of the array to newly created file
  for (i = 0; i < arr_size; ++i){
    fprintf(out, "%s", array[i]);
  }
  
  printf("\nFile copied successfully!");
 
  // Close the outfile
  fclose(out);

}

int main(int argc, char *argv[]){

  char *infile;
  char *outfile;
  char *passphrase;
  char *operation;
  
  int input_len;

  // Variable for the storage of file contents
  char temp_array[4096]; // Contains elements character-by-character
  char processed_array[4096][100]; // Elements are in string format

  // Check input arguments: <infile> <outfile> <passphrase> <operation>
  if (argc == 5){ 
    infile = argv[1];
    outfile = argv[2];
    passphrase = argv[3];
    operation = argv[4];
    printf("The input file is %s\n", infile);
    printf("The output file is %s\n", outfile);
    printf("The passphrase is %s\n", passphrase);
    printf("The operation is %s\n", operation);
  } else { 
    return 0; // Error
  }

  // Read input file and store contents in the array
  input_len = read_file(infile, temp_array);


  int start = 0;
  int end;
  int j = 0;
  int processed_len;

  // Convert array of individual characters into an array of strings
  for (int i=0; i<input_len; ++i) {
    if(temp_array[i] == 10 || i == (input_len-1)) {
      end = i;
      char subset[end-start+1];
      strncpy(subset, &temp_array[start], end - start + 1);
      subset[end - start + 1] = '\0';
      strcpy(processed_array[j], subset);
      start = end+1;
      ++j;
    }
  }

  processed_len = j;

  // Write contents of the array to an output file
  write_file(outfile, processed_array, processed_len);

  return 0; 
}
