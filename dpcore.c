#include <stdio.h> 
#include <stdlib.h>

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

int main(int argc, char *argv[]){

  char *infile;
  char *outfile;
  char *passphrase;
  char *operation;

  FILE *fp1, *fp2;
  char ch;

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
    return 1; // Error
  }
 
  // Open input file
  fp1 = fopen(infile, "r");
 
  // Error handling
  if (fp1 == NULL){
    puts("Cannot open file");
    exit(0);
  }
 
  // Create outfile
  fp2 = fopen(outfile, "w");
 
  // Error handling
  if (fp2 == NULL){
    puts("Not able to create file");
    fclose(fp1);
    exit(0);
  }
 
  // TEST: Copy contents of infile to outfile, character by character
  while ((ch = fgetc(fp1)) != EOF){
    fputc(ch, fp2);
  }
 
  printf("File copied successfully!\n");
 
  // Close both files
  fclose(fp1);
  fclose(fp2);

  return 0; 
}
