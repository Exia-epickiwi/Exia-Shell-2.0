#include <stdio.h>
#include <stdlib.h>
//Taille des clefs de langue
#define KEY_LENGTH 128
//Taille maximum d'une commande
#define COMMAND_LENGTH 256
//Fichier relatif aux couleurs
#include "color.h"
#include "config.h"
#include "config.c"
#include "language.h"
#include "language.c"
#include "exec.c"

//Fonction init du shell
//Parametres :
//  argc : Nombre d'arguments passés
//  argv : Tableau d'arguments passés
//Renvoie : Code de sortie du programme
int main(int argc, char *argv[]){
  //Chargement de la configuration
  Config *configuration = loadConfig();
  switch(configuration->mode){
    case 0:
      //Mode expert
      //return initExpertMode();  TODO Non implémenté
    break;
    case 1:
      //Mode pas a pas
      //return initAssistantMode(); TODO Non implémenté
    break;
    case 2:
      //Mode naturel
      //return initNaturalMode(); TODO Non implémenté
    break;
    default:
      printf(COLOR_RED "%s" COLOR_RESET " %s\n",toLocaleString(configuration->lang,"error.error"),toLocaleString(configuration->lang,"error.unknownMode"));
      return EXIT_FAILURE;
    break;
  }
}
