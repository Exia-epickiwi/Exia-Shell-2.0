#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "load.h"
//Nombre de caractère maximale
#define LINE_CHARACTER_MAX 150
//Prototype type de c'est fonction
char *separationChaine(char config[], char separation);
void moveIndex(char config[], int start, int end);

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
    fputs("mode=0\nlanguage=fr\nprompt=exsh\n", fichierConfig);
    //Puis l'insère dans le la config.
    config->mode = 0;
    strcpy(config->locale, "fr");
    strcpy(config->prompt, "exsh");
    config->lang = NULL;
  } else {
    //Initiale un tableau char comportant la ligne en cours de lecture.
    char lineConfig[LINE_CHARACTER_MAX];
    //Récupére chaque ligne du fichierConfig
    while(fgets(lineConfig, LINE_CHARACTER_MAX, fichierConfig)){
      //Permet de garder en mémoire le mot clef de la config
      char *motClef = separationChaine(lineConfig, '=');
      //Si c'est égale à mode
      if(strcmp(motClef, "mode") == 0){
        //si c'est entre 0 et 2 alors il l'enregistre sinon c'est 0
        if(lineConfig[0] <= '2' && lineConfig[0] >= '0'){
          config->mode = atoi(lineConfig);
        } else {
          config->mode = 0;
        }
      }
      //si c'est égale à language
      else if(strcmp(motClef, "language") == 0){
        //Copie le reste de la lineConfig dans la config de locale
        strcpy(config->locale, lineConfig);
      }
      //si c'est égale à prompt
      else if(strcmp(motClef, "prompt") == 0){
        //Cope le reste de la lineConfig dans la config de prompt
        strcpy(config->prompt, lineConfig);
      }
    }
    printf("Initialisation finish\n");
    printf("%s> \n",config->prompt);
  }
  //Ferme le fichier correctement
  fclose(fichierConfig);
  //retourne la structure config initialisé
  return config;
}
//fonction pour séparer une chaine de caractère à partir d'un char de séparation
char *separationChaine(char config[], char separation){
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
