#include <unistd.h>

int changeWorkingDirectory(char *path){
  return chdir(path);
}
