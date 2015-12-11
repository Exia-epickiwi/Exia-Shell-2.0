#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "load.h"
//Nombre de caractère maximale
#define LINE_CHARACTER_MAX 150;

//Fonction permettant de charger des variables à partir d'un dossier
Config *loadConfig(){
  //initialie et ouvre le fichier en lecture seul
  FILE *fichierConfig;
  fichierConfig = fopen("config.txt", "r");
  //Initiale la structure
  Config *config = malloc(sizeof(Config));
  //Si le fichierConfig n'existe pas alors il l'écrit
  if(fichierConfig == NULL){
    fichierConfig = fopen("config.txt", "w");
    //Ecrit dans le fichier le mode, langue et le prompt par défaut
    fputs("mode : 0\nlanguage : fr\nprompt : exsh\n", fichierConfig);
    //Puis l'insère dans le la config.
    config->mode = 0;
    strcpy(config->locale, "fr");
    strcpy(config->prompt, "exsh");
    config->lang = NULL;

  } else {
    //Initiale un tableau char comportant la ligne en cours de lecture.
    char lineConfig[LINE_CHARACTER_MAX];
    while(fgets(ligneConfig, LINE_CHARACTER_MAX, fichierConfig)){
    }
  }
  //Ferme le fichier correctement
  fclose(fichierConfig);
  //retourne la structure config initialisé
  return config;
}
