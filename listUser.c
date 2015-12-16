#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "listUser.h"
#include "language.h"
#include "config.h"
#include "color.h"

//Fonction affichant la liste des utilisateurs disponibles sur le système
//Paramètres :
//  config : structure de configuration
void listUser(Config *config){
  //Ouvre le fichier pssword
  FILE *fileUser = fopen("/etc/passwd", "r");
  if(fileUser == NULL){
    printf("%s\n", toLocaleString(config->lang, "error.userNull"));
    return;
  }
  //Affiche les entêtes du tableau
  char user[255];
  printf(COLOR_GREEN"UID\t|  "COLOR_YELLOW" USER\n-------------------\n"COLOR_RESET);
  //Recupère lignes par ligne le contenu
  while(fgets(user, 255, fileUser)){
    //Recupèration du nom d'utilisateur
    char *name = strtok(user, ":");
    strtok(NULL, ":");
    //affichage uniquement si l'id est superieur a 1000
    char *uid = strtok(NULL, ":");
    if(atoi(uid) >= 1000 || atoi(uid) == 0) {
      printf(COLOR_GREEN"%s\t|  "COLOR_YELLOW" %s\n"COLOR_RESET, uid, name);
    }
  }
}
