#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"
#include "config.h"
//Nombre de caractère maximale
#define LINE_CHARACTER_MAX 150

char *removeN(char *tableau);

void toLog(char *string){
  //Ouvre le fichier
  FILE *fileLog = fopen(PATH_LOG, "a");

  //Initialise la date de la machine
  time_t t;
  time(&t);

  //Initialise les tableaux qui serviront à écrire dans le fichier
  char logString[80];
  char *date = ctime(&t);
  //Formate une chaîne de caractère avec la date et la commande
  sprintf(logString, "[%s]-%s\n", removeN(date), string);

  //si le fichier n'existe pas alors il créer un nouveau.
  if(fileLog == NULL){
    fileLog = fopen(PATH_LOG, "w");
    //Insère la première ligne dans le fichier
    fputs(logString, fileLog);
  } else {
    //Insère la ligne
    fputs(logString, fileLog);
  }
  //Ferme le fichier correctement
  fclose(fileLog);
}
//Fonction qui permet d'enlever le \n par un \0
char *removeN(char *tableau){
  //Initialise le pointeur d'index
  char *index = NULL;
  //Recherche la valeur demandé dans le tableau
  index = strchr(tableau, '\n');
  //Si trouvé alors on le modifie
  if(index != NULL){
    *index = '\0';
  }
  //Retourne le tableau si il doit être retournée
  return tableau;
}

void loadHistory(Config *config){
  int numberCommande = 0;
  FILE *file = fopen(PATH_LOG, "r");
    if(file != NULL){
      char ligne[256];
      while(fgets(ligne, 256, file)){
        numberCommande++;
      }
    }
  fclose(file);

  file = fopen(PATH_LOG, "r+");
  HeadLog *headLog = malloc(sizeof(HeadLog));
  headLog->first = NULL;
  headLog->length = 0;
  config->history = headLog;
  if(file == NULL){
    file = fopen(PATH_LOG, "w");
  } else {
    //Initialise un tableau char comportant la ligne en cours de lecture.
    char lineConfig[LINE_CHARACTER_MAX];
    //Récupère chaque ligne du fileConfig
    while(fgets(lineConfig, LINE_CHARACTER_MAX, file)){
      if(numberCommande-5 <= 0){
        ElementLog *elementLog = malloc(sizeof(ElementLog));
        strtok(lineConfig, "-");
        strcpy(elementLog->command, strtok(NULL, "\0"));
        elementLog->next = config->history->first;
        config->history->first = elementLog;
      } else {
        numberCommande--;
      }
    }
  }
}

void seeLog(Config *config){
  int index = 0;
  ElementLog *elementLog = config->history->first;
  for(;elementLog != NULL; index++){
    printf("%s", elementLog->command);
    if(elementLog->next == NULL) break;
    elementLog = elementLog->next;
  }
}
