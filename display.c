#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fonction affichant le prompt personnalisé
//Paramètres :
//  prompt : Prompt personnalisé
void printPrompt(char *prompt){
  printf("%s> ",prompt);
}

//Fonction récupèrant de manière sécurisée une entrée clavier
//Paramètres :
//  string : Chaîne a remplir
//  max : Nombre maximum de caractères
//Renvoie : 1 si tout c'est bien passé ou 0 si il y a une erreur
int getKeyboard(char *string,int max){
  char *nPos = NULL;
  //Récuperation de l'entrée de clavier
  if(fgets(string,max,stdin) != NULL){
    //Recherche d'un \n
    nPos = strchr(string,'\n');
    if(nPos != NULL){
      //Remplacement par un \0
      *nPos = '\0';
    }
    return 1;
  } else {
    return 0;
  }
}
