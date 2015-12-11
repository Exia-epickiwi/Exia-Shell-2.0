#include <string.h>
#include <unistd.h>
#include "exec.h"

int execCommand(char *str){
  char **args = NULL;
  char *p    = strtok (str, " ");
  int length = 0, i;
  while (p) {
    args = realloc (args, sizeof (char*) * ++length);
    args[length-1] = p;
    p = strtok (NULL," ");
  }

  int pid = fork();
  if(pid == 0){
    execv(args[0],args);
    return -1;
  }else{
    return pid;
  }
}
