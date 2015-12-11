#include <string.h>
#include "exec.h"

int execCommand(char *command){
  char *args[50];
  char path[COMMAND_LENGTH];
  int length = splitCommand(command,args,path);
  int i;
  printf("->%s\n",path);
  for(i = 0; i<length; i++){
    printf("%s\n",args[i]);
  }
}

int splitCommand(char *str, char **splitstr,char *program)
{
  char *p;
  int i=0;

  p = strtok(str," ");
  while(p!= NULL)
  {
    if(i > 0){
      splitstr[i] = malloc(strlen(p) + 1);
      if (splitstr[i-1])
        strcpy(splitstr[i-1], p);
    }else{
      strcpy(program,p);
    }
    i++;
    p = strtok(NULL, " ");
  }
  return i;
}
