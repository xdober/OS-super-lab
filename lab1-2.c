#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( ) {
  char src_name[255], tgt_name[255], swap[1024];
  FILE *fp_src, *fp_tgt;// fp source and dp target;
  int j = 1024;//read 1024 bytes one time;
  int flag_name_check = 1;
  do {
    printf("please input the source file name:\n");
    scanf("%s", src_name);
    getchar();
    printf("please input the target file name\n", tgt_name);
    scanf("%s", tgt_name);
    getchar();
    flag_name_check = !strcmp(src_name, tgt_name);
    if (flag_name_check) {
      printf("Error! your source flie and target file have the same name.\n");
    }
  } while(flag_name_check);
  printf("source file: %s\ntarget file: %s\n", src_name, tgt_name);
  printf("copy processing...\n");
  fp_src = fopen(src_name, "r");
  fp_tgt = fopen(tgt_name, "w");
  if (!fp_src) {
    printf("error open source file\n");
    return 0;
  }
  if (!fp_tgt) {
    printf("error open target file\n");
    return 0;
  }
  while ( j == 1024) {//read uncomplete
    j = fread(swap, 1, 1024, fp_src);
    fwrite(swap, 1, j, fp_tgt);
  }
  fclose(fp_src);
  fclose(fp_tgt);

  printf("copy finished!\n");

  return 0;
}
