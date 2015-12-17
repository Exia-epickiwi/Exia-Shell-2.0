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
    //Si le fichier n'existe pas alors aucun utilisateur
    printf("%s\n", toLocaleString(config->lang, "error.userNull"));
    return;
  }
  //Affiche les entêtes du tableau
  char user[255];
  printf("\t"COLOR_GREEN"UID\t|  "COLOR_YELLOW" USER\n\t"COLOR_MAGENTA"-----------------\n"COLOR_RESET);
  //Recupère lignes par ligne le contenu
  while(fgets(user, 255, fileUser)){
    //Recupèration du nom d'utilisateur
    char *name = strtok(user, ":");
    //La second valeur est x donc on la garde pas
    strtok(NULL, ":");
    //La troisième valeur est l'uid de l'utilisateur donc on la garde.
    char *uid = strtok(NULL, ":");
    //On rajoute tout PID de 1000 sans le nobody et on rajoute le root au PID = 0
    if((atoi(uid) >= 1000 || atoi(uid) == 0) && strcmp(name, "nobody") != 0) {
      printf("\t"COLOR_GREEN"%s\t|  "COLOR_YELLOW" %s\n"COLOR_RESET, uid, name);
    }
  }
}
