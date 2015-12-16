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
  char commande[250];
  do {
    char cmd[256];
    printPrompt(configuration->prompt); //Affiche le prompt
    if(getKeyboard(commande, 256) == 0) return 0; //récupére les données transmit par le clavier. Si null alors return 0
    toLog(commande); //Ecrire dans le log la commande
    execCommandSync(commande, configuration); //Exécute la commande.
  }while(1);
 return 0;
}
