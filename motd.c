#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "motd.h"

void printStartsInfos(char *locale){
  char path[] = PATH_MOTD;
  char *nameFile = strcat(path, locale);
  FILE *file = fopen(nameFile, "r");
  char line[256];
  while(fgets(line, 256, file)){
    printf("%s", line);
  }
}
