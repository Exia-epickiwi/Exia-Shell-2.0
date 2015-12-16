#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "motd.h"

void printStartsInfos(char *locale){
  //récupére la constante du PATH_MOTD
  char path[] = PATH_MOTD;
  //on addition les 2 chaines de caractéres
  char *nameFile = strcat(path, locale);
  //Ouvre le fichier
  FILE *file = fopen(nameFile, "r");
  char line[256];
  //parcour tout les lignes du fichier
  while(fgets(line, 256, file)){
    //affiches les lignes
    printf("%s", line);
  }
  printf("\n");
  //ferme le fichier
  fclose(file);
}
