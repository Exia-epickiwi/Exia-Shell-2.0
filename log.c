#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"
#include "config.h"
//Nombre de caractère maximale
#define LINE_CHARACTER_MAX 150

void defile(HeadLog headLog);
void emfile(HeadLog *headLog, ElementLog * elementLog);

char *removeN(char *tableau);

void toLog(char *string){
  //Ouvre le fichier
  FILE *fileLog = fopen(PATH_LOG, "a");

  //Initialise la date de la machine
  time_t t;
  time(&t);

  //Initiale les tableaux qui serviront à écrire dans le fichier
  char logString[80];
  char *date = ctime(&t);
  //Formate une chaine de caractère avec la date et la commande
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
  //initialise le pointeur d'index
  char *index = NULL;
  //recherche la valeur demandé dans le tableau
  index = strchr(tableau, '\n');
  //Si trouvé alors on le modifie
  if(index != NULL){
    *index = '\0';
  }
  //Retourne le tableau si il doit être retournée
  return tableau;
}

void loadHistory(Config *config){
  FILE *file = fopen(PATH_LOG, "r+");
  HeadLog *headLog = malloc(sizeof(HeadLog));
  headLog->first = NULL;
  headLog->length = 0;
  config->history = headLog;

  if(file == NULL){
    file = fopen(PATH_LOG, "w");
  } else {
    //Initiale un tableau char comportant la ligne en cours de lecture.
    char lineConfig[LINE_CHARACTER_MAX];
    //Récupére chaque ligne du fileConfig
    while(fgets(lineConfig, LINE_CHARACTER_MAX, file)){
      ElementLog *elementLog = malloc(sizeof(ElementLog));
      strtok(lineConfig, "-");
      strcpy(elementLog->command, strtok(NULL, "\0"));
        emfile(headLog, elementLog);
      config->history->length++;
      if(config->history->length > 5) {
        defile(headLog);
        emfile(headLog);
      }
    }
  }
}
void emfile(HeadLog *headLog, ElementLog * elementLog){
  if(headLog->first != NULL){
    ElementLog *actual = HeadLog->first;
    while(actual != NULL){
      actual = actual->next;
    }
    actual->next = elementLog;
  } else {
    headLog->first = elementLog;
  }
}

void defile(HeadLog headLog){
  if(headLog->first != NULL){
    ElementLog *elementLog = headLog->first;
    headLog->first = elementLog->next;
    free(elementLog);
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
