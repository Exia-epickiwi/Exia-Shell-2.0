#include <string.h>
#include <unistd.h>
#include "exec.h"

//Fonction executant un programme suivant une commande
//Paramètres :
//  str : Tableau représentant la chaine de caractère de la commande
//Renvoie : le pid du process executé ou -1 si il y a eu une erreur
int execCommand(char *str){
  char **args = NULL;
  char *p    = strtok (str, " ");
  int length = 0, i;
  while (p) {
    args = realloc (args, sizeof (char*) * ++length);
    args[length-1] = p;
    p = strtok (NULL," ");
  }

  int pid = fork();
  if(pid == 0){
    execv(args[0],args);
  }else if(pid < 0){
    return -1;
  }else{
    return pid;
  }
}

//Fonction executant un programme et attendant la fin de clui ci
//Paramètres :
//  str : Tableau représentant la chaine de caractère de la commande
//Renvoie : 1 si tout c'est bien passé si non 0
int execCommandSync(char *command){
  int pid = execCommand(command);
  if(pid > 0){
    wait(pid);
    return 1;
  } else {
    return 0;
  }
}
