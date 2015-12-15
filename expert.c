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
  char commande[250];
  do {
    char cmd[256];
    printPrompt(configuration->prompt);
    if(getKeyboard(commande, 256) == 0) return 0;
    toLog(commande);

    if(commande[0] != '.' && commande[0] != '/') sprintf(cmd, "%s%s", pathCommande, commande);
    else sprintf(cmd, "%s", commande);
    execCommandSync(cmd, configuration);

  }while(1);
 return 0;
}
