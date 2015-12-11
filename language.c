#include <stdlib.h>
#include <string.h>
#include "language.h"

Language* loadLanguage(char *file){
  //On charge le fichier donné en paramètres
  FILE *langFile = fopen(file,"r");
  //Verification de l'existance du fichier
  if(langFile == NULL){
    return NULL;
  }
  Language *lang = parseLanguageFile(langFile);
  //fermeture du fichier
  fclose(langFile);
  //Retour de la liste chainée
  return lang;
}

Language* parseLanguageFile(FILE *langFile){
  //Initialisation de la liste chainée
  Language *lang = malloc(sizeof(Language));
  //Lecture du fichier ligne par ligne
  char line[MAX_LANG_LINE_LENGTH] = "";
  while(fgets(line,MAX_LANG_LINE_LENGTH,langFile)){
    //Recherche de la clé
    char key[KEY_LENGTH] = "";
    int i;
    for (i = 0; line[i] != '='; i++){
      key[i] = line[i];
    }
    key[i] = '\0';
    //Enregistrement de la valeur associée
    char value[COMMAND_LENGTH] = "";
    int j = 0;
    for(i = i+1; line[i] != '\r' && line[i] != '\n' && i<strlen(line); i++){
      value[j] = line[i];
      j++;
    }
    value[j] = '\0';
    //Ajout d'un element a la chaine
    addLanguageString(lang,key,value);
  }
  return lang;
}

void addLanguageString(Language *target,char *key, char *value){
  //Allocation dynamique du nouvel element
  LangString *newString = malloc(sizeof(LangString));
  strcpy(newString->key,key);
  strcpy(newString->value,value);
  //Ajout des adresses a la liste chainée
  if(target->first == NULL){
    target->first = newString;
  }else{
    target->last->next = newString;
  }
  target->last = newString;
}

char* toLocaleString(Language *lang,char *key){
  LangString *next = lang->first;
  int i;
  while(next != NULL){
    if(strcmp(next->key,key) == 0){
      return next->value;
    }
    next = next->next;
  }
}
