#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"

char *removeN(char *tableau);

void toLog(char *string){
  //Ouvre le fichier
  FILE *fileLog = fopen(PATH_LOG, "r+");

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
    fileLog = fopen("exsh.log", "w");
    //Insère la première ligne dans le fichier
    fputs(logString, fileLog);
  } else {
    //Situe le curseur en fin du fichier
    fseek(fileLog, 0, SEEK_END);
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
