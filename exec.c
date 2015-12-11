#include <string.h>
#include "exec.h"

int execCommand(char *command){
  char *args[50];
  int length = splitCommand(command,args);
  int i;
  for(i = 0; i<length; i++){
    printf("%s\n",args[i]);
  }
}

int splitCommand(char *str, char **splitstr)
{
  char *p;
  int i=0;

  p = strtok(str," ");
  while(p!= NULL)
  {
    splitstr[i] = malloc(strlen(p) + 1);
    if (splitstr[i])
      strcpy(splitstr[i], p);
    i++;
    p = strtok (NULL, " ");
  }
  return i;
}
