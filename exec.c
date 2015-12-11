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
  }else if(pid < 0){
    return -1;
  }else{
    return pid;
  }
}

int execCommandSync(char *command){
  int pid = execCommand(command);
  if(pid > 0){
    wait(pid);
    return 1;
  } else {
    return 0;
  }
}
