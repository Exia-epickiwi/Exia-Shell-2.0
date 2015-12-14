#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expert.h"
#include "display.h"
#include "exec.h"
#include "config.h"
#include "log.h"

int initExpertMode(Config *configuration) {
  char commande[256];
  char pathCommande[] = "/bin/";
  do {

    printPrompt(configuration->prompt);
    if(getKeyboard(commande, 256) == 0) return 0;

    if(strcmp(commande, "exit") == 0) break;
    if((commande[0] != '.' && commande[1] != '/') || commande[0] != '/') strcat(pathCommande, commande);
    execCommandSync(pathCommande);

    toLog(commande);
  }while(1);
 return 0;
}
