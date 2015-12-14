#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expert.h"
#include "display.h"
#include "exec.h"
#include "config.h"
#include "log.h"

int initExpertMode(Config *configuration) {
  //initialise la chemin des exécutables
  char pathCommande[] = "/bin/";
  do {
    char cmd[256];
    printPrompt(configuration->prompt);
    if(getKeyboard(cmd, 256) == 0) return 0;

    if(strcmp(cmd, "exit") == 0) break;

    if((cmd[0] != '.' && cmd[1] != '/') || cmd[0] != '/') sprintf(cmd, "%s%s", pathCommande, cmd);
    execCommandSync(cmd);
    toLog(cmd);
  }while(1);
 return 0;
}
