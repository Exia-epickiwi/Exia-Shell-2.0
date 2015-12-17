#include <stdio.h>
#include <stdlib.h>

#include "main.h"
//Fichier relatif aux couleurs
#include "color.h"

#include "config.h"
#include "language.h"
#include "assistant.h"
#include "motd.h"
#include "display.h"
#include "exec.h"
#include "hanoi.h"
#include "natural.h"
#include "expert.h"
//Fonction init du shell
//Paramètres :
//  argc : Nombre d'arguments passés
//  argv : Tableau d'arguments passés
//Renvoie : Code de sortie du programme
int main(int argc, char *argv[]){
  //Chargement de la configuration
  Config *configuration = loadConfig();
  printStartsInfos(configuration->locale);
  switch(configuration->mode){
    case 0:
      //Mode expert
      return initExpertMode(configuration);
    break;
    case 1:
      //Mode pas à pas
      return initAssistantMode(configuration);
    break;
    case 2:
      //Mode naturel
      return initNaturalMode(configuration);
    break;
    default:
      //Erreur si le mode n'est pas reconnu
      printf(COLOR_RED "%s" COLOR_RESET " %s\n",toLocaleString(configuration->lang,"error.error"),toLocaleString(configuration->lang,"error.unknownMode"));
      return EXIT_FAILURE;
    break;
  }
}
