#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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

int dp_request(struct dp_cmd_desc *){
  return 1;
}

const char *read_file(char *directory) {

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(directory, "r");

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
  }

  fclose(fp);
  if (line) {
    free(line);
  }
  
  return line;
}

int main(){
  
  // Initialization of temporary variables
  struct dirent *pDirent_top;
  DIR *pDir_top;
  struct dirent *pDirent_bot;
  DIR *pDir_bot;

  FILE* ptr;
  char directory[] = ""; // Insert directory here
  
  pDir_top = opendir(directory);
  
  if (pDir_top == NULL) {
    printf("Cannot open directory '%s'\n", directory);
    return 1;
  }
  
  return 0;
}
