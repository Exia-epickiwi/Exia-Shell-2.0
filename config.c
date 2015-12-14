#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "language.h"
#include "log.h"
//Nombre de caractère maximale
#define LINE_CHARACTER_MAX 150
//Prototype type de c'est fonction
char *separationChain(char config[], char separation);
void moveIndex(char config[], int start, int end);

//Fonction permettant de charger des variables à partir d'un dossier
Config *loadConfig(){
  //initialie et ouvre le fichier en lecture seul
  FILE *fileConfig;
  fileConfig = fopen(PATH_PROFILE, "r");
  //Initiale la structure
  Config *config = malloc(sizeof(Config));

  //Si le fileConfig n'existe pas alors il l'écrit
  if(fileConfig == NULL){
    //On insere des valeurs par défaut
    config->mode = 0;
    config->lang = NULL;
    strcpy(config->locale, "fr");
    strcpy(config->prompt, "exsh");

  } else {
    //Initiale un tableau char comportant la ligne en cours de lecture.
    char lineConfig[LINE_CHARACTER_MAX];
    //Récupére chaque ligne du fileConfig
    while(fgets(lineConfig, LINE_CHARACTER_MAX, fileConfig)){
      //Permet de garder en mémoire le mot clef de la config
      char *keyword = separationChain(lineConfig, '=');
      //Si c'est égale à mode
      if(strcmp(keyword, "mode") == 0){
        config->mode = atoi(lineConfig);
      }
      //si c'est égale à language
      else if(strcmp(keyword, "language") == 0){
        //Copie le reste de la lineConfig dans la config de locale
        strcpy(config->locale, lineConfig);
      }
      //si c'est égale à prompt
      else if(strcmp(keyword, "prompt") == 0){
        //Cope le reste de la lineConfig dans la config de prompt
        strcpy(config->prompt, lineConfig);
      }
    }
    //Initialisation de la langue
    char path[] = PATH_LANGUAGE;
    config->lang = loadLanguage(strcat(path,config->locale));
  }
  //Charge l'historique des anciennes sessions
  loadHistory(config);
  //Ferme le fichier correctement
  fclose(fileConfig);
  //retourne la structure config initialisé
  return config;
}
//fonction pour séparer une chaine de caractère à partir d'un char de séparation
char *separationChain(char config[], char separation){
  //initiale les variables des boucles for => Pour certain c cela ne marche pas les déclarations dans les boucles for
  int a, b;
  //boucle for qui parcour le tableau config[]
  for (a = 0; a < LINE_CHARACTER_MAX && (config[a] != '\0' || config[a] != '\n'); a++) {
    //Si le caractère est égale au caractère
    if(config[a] == separation){
      //Créer un nouveau tableau et initialise tout les cases
      char *s = calloc(a, sizeof(char));
      //Met le tableau pour sauvegarder et renvoie un tableau de char
      for (b = 0; b < a; b++) {
        s[b] = config[b];
      }
      //Déplace le tableau en enlevant le tableau s[]
      moveIndex(config, a+1, LINE_CHARACTER_MAX);
      //renvoie le tableau s
      return s;
    }
  }
  return NULL;
}
//Fonction permettant de déplacer une chaine de caractère dans un tableau
void moveIndex(char config[], int start, int end){
  int a;
  //Boucle for qui parcour le tableau config[]
  for (a = 0; a < end && config[a] != '\0'; a++) {
    //Remplace l'index de config[a] par l'index start+a
    config[a] = config[start+a];
    //si le caractère est égale à \n et \r alors le remplace par \0
    if(config[a] == '\n') {
      config[a] = '\0';
    } else if(config[a] == '\r') {
      config[a] = '\0';
    }
  }
}
