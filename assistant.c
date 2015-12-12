#include <stdlib.h>
#include "assistant.h"
#include <string.h>

int initAssistantMode(Config *config){
  Category *index = loadCategories(PATH_ASSISTANT);
  if(index == NULL){
    printf("%s %s\n",toLocaleString(config->lang,"error.error"),toLocaleString(config->lang,"error.loadCategories"));
    exit(EXIT_FAILURE);
  }
}

Category* loadCategories(char *path){
  //Ouvrir un fichier
  FILE *categoryFile = fopen(path,"r");
  //SI il y a erreur
  if(categoryFile == NULL)
    return NULL;
  //Lecture de chaque ligne
  return parseCategory(categoryFile,ftell(categoryFile),NULL);
}

Category* parseCategory(FILE *file,long position,Category *parent){
  //On place le curseur a la position donnée
  fseek(file,position,SEEK_SET);
  //Buffer de caracteres
  char buffer[MAX_CATEGORY_LINE_LENGTH];
  //Chargement de la première ligne
  fgets(buffer,MAX_CATEGORY_LINE_LENGTH,file);
  //calcul de la profondeur
  int baseDeep = getDeep(buffer);
  //On replace a la base
  fseek(file,position,SEEK_SET);
  //Si le parent est nul on crée une nouvelle catégorie
  if(parent == NULL){
    parent = malloc(sizeof(Category));
    parent->first = NULL;
    parent->last = NULL;
  }
  //On lit alors les lignes du fichier
  int lastPosition = position;
  CategoryElement *lastElement = NULL;
  while(fgets(buffer,MAX_CATEGORY_LINE_LENGTH,file) != NULL){
    //Suppression du \n final
    strcpy(buffer,strtok(buffer,"\r"));
    //Verification que l'on est toujours soit au dessus soit au même niveau
    int deep = getDeep(buffer);
    if(deep < baseDeep){
      break;
    }
    if(deep==baseDeep){
      addCategoryElement(parent,getCategoryLineName(buffer),NULL,NULL);
      lastElement = parent->last;
      char *command = getCategoryCommand(buffer);
      if(command != NULL){
        CategoryCommand *newCommand = malloc(sizeof(CategoryCommand));
        strcpy(newCommand->command,command);
        free(command);
        lastElement->command = newCommand;
      }
    } else if(deep > baseDeep) {
      lastElement->under = parseCategory(file,lastPosition,NULL);
    }
    lastPosition = ftell(file);
  }
  fseek(file,lastPosition,SEEK_SET);
  return parent;
}

int getDeep(char *buffer){
  int deep = 0;
  while (buffer[deep]==' ') {
    deep++;
  }
  return deep;
}

void addCategoryElement(Category *parent,char *name,Category *under, CategoryCommand *command){
  CategoryElement *element = malloc(sizeof(CategoryElement));
  element->under = under;
  element->command = command;
  element->next == NULL;
  strcpy(element->name,name);
  if(parent->first == NULL){
    parent->first = element;
  }else{
    parent->last->next = element;
  }
  parent->last = element;
}

char* getCategoryLineName(char* buffer){
  char *result = malloc(sizeof(char)*COMMAND_LENGTH);
  int i,j = 0;
  for(i = 0;buffer[i] != ':' && i<strlen(buffer);i++){
    if(buffer[i] != ' '){
      result[j] = buffer[i];
      j++;
    }
  }
  return result;
}

char* getCategoryCommand(char* buffer){
  int finded = 0;
  int i,j = 0;
  char *result = NULL;
  for(i = 0;i<strlen(buffer);i++){
    if(buffer[i] == ':' && finded != 1){
      result = malloc(sizeof(char)*COMMAND_LENGTH);
      finded = 1;
    }else if(finded == 1){
      result[j] = buffer[i];
      j++;
    }
  }
  if(finded == 1){
    return result;
  }else{
    return NULL;
  }
}

void printCategoryTree(Category *index,int deep){
  CategoryElement *next = index->first;
  while(next != NULL){
    int i;
    for(i=0;i<=deep;i++){
      printf("-");
    }
    printf(">%s",next->name);
    if(next->command != NULL){
      printf(" / %s",next->command->command);
    }
    printf("\n");
    if(next->under != NULL){
      printCategoryTree(next->under,deep+1);
    }
    next = next->next;
  }
}
