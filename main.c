#include <stdio.h>
#include <stdlib.h>
//Taille des clefs de langue
#define KEY_LENGTH 128
//Taille maximum d'une commande
#define COMMAND_LENGTH 256
//Fichier relatif aux couleurs
#include "color.h"
#include "load.h"

//Fonction init du shell
//Parametres :
//  argc : Nombre d'arguments passés
//  argv : Tableau d'arguments passés
//Renvoie : Code de sortie du programme
int main(int argc, char *argv[]){
  //Chargement de la configuration
  Config *configuration = loadConfig();
  /*switch(Config->mode){
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
      printf(COLOR_RED "Erreur!" COLOR_RESET " le mode %d n'est pas un mode connu\n",config->mode); TODO Gestion du multilangue
      printf("Les modes disponibles sont :\n0 : Mode expert\n1 : Mode assistant\n2 : Mode naturel\n");
      return EXIT_FAILURE;
    break;
  }*/
}
