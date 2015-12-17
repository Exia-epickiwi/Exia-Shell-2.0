#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "motd.h"

//Fonction affichant le message de bienvenue
//Paramètres :
//  locale : code de langue de l'utilisateur
void printStartsInfos(char *locale){
  //récupère la constante du PATH_MOTD
  char path[] = PATH_MOTD;
  //on additione les 2 chaînes de caractères
  char *nameFile = strcat(path, locale);
  //Ouvre le fichier
  FILE *file = fopen(nameFile, "r");
  char line[256];
  //parcourt toutes les lignes du fichier
  while(fgets(line, 256, file)){
    //affiches les lignes
    printf("%s", line);
  }
  printf("\n");
  //ferme le fichier
  fclose(file);
}
