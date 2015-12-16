#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "listUser.h"
#include "language.h"
#include "config.h"
#include "color.h"

void listUser(Config *config){
  FILE *fileUser = fopen("/etc/passwd", "r");
  if(fileUser == NULL){
    printf("%s\n", toLocaleString(config->lang, "error.userNull"));
    return;
  }
  char user[255];
  printf(COLOR_GREEN"UID\t|  "COLOR_YELLOW" USER\n-------------------\n"COLOR_RESET);
  while(fgets(user, 255, fileUser)){
    char *name = strtok(user, ":");
    strtok(NULL, ":");
    char *uid = strtok(NULL, ":");
    if(atoi(uid) >= 1000 || atoi(uid) == 0) {
      printf(COLOR_GREEN"%s\t|  "COLOR_YELLOW" %s\n"COLOR_RESET, uid, name);
    }
  }
}
