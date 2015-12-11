#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"

char *removeN(char *tableau);

void toLog(char *string){
  FILE *fileLog = fopen("exsh.log", "r+");

  time_t t;
  time(&t);
  char logString[80];
  char *date = ctime(&t);
  sprintf(logString, "[%s] %s", removeN(date), string);
  puts(logString);

  if(fileLog == NULL){
    fileLog = fopen("exsh.log", "w");
    fputs(logString, fileLog);
  } else {
    fseek(fileLog, 0, SEEK_END);
    fputs(logString, fileLog);
  }
  fclose(fileLog);
}

char *removeN(char *tableau){
  char *index = NULL;
  index = strchr(tableau, '\n');
  if(index != NULL){
    *index = '\0';
  }
  return tableau;
}
