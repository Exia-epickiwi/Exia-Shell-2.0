#include <stdlib.h>
#include <string.h>
#include "assistant.h"
#include "display.h"
#include "exec.h"

int initAssistantMode(Config *config){
  Category *index = loadCategories(PATH_ASSISTANT);
  if(index == NULL){
    printf("%s %s\n",toLocaleString(config->lang,"error.error"),toLocaleString(config->lang,"error.loadCategories"));
    exit(EXIT_FAILURE);
  }
  printCategoryTree(index,0);
  Category *displayed = index;
  while(1){
    printPrompt(config->prompt);
    if(index == displayed){
      printf("%s\n", toLocaleString(config->lang,"assistant.indexPrompt"));
    } else {
      printf("%s\n", toLocaleString(config->lang,displayed->parent->name));
    }
    int maxChoice = printCategoryElements(config->lang,displayed);
    printf("%s (1-%d) : ",toLocaleString(config->lang,"assistant.promptChoice"),maxChoice);
    char buffer[5] = {'\0'};
    getKeyboard(buffer,5);
    displayed = performCategoryAction(config->lang,displayed,buffer,maxChoice);
    printf("\n");
  }
}

int printCategoryElements(Language *lang,Category *cat){
  CategoryElement *next = cat->first;
  int i = 1;
  while(next != NULL){
    printf("%d - %s\n",i,toLocaleString(lang,next->name));
    i++;
    next = next->next;
  }
  if(cat->parent != NULL){
    printf("%d - %s\n",i,toLocaleString(lang,"assistant.back"));
  } else {
    i--;
  }
  printf("\n");
  return i;
}

Category* performCategoryAction(Language *lang,Category *nowCategory,char *input,int maxInput){
  int choice = atoi(input);
  if(choice == 0){
    printf(COLOR_RED "\n%s" COLOR_RESET " %s\n",toLocaleString(lang,"error.error"),toLocaleString(lang,"error.assistant.unknownChoice"));
    return nowCategory;
  } else if(choice > maxInput || choice < 1){
    printf(COLOR_RED "\n%s" COLOR_RESET " %s\n",toLocaleString(lang,"error.error"),toLocaleString(lang,"error.assistant.outChoice"));
    return nowCategory;
  }
  int i = 1;
  CategoryElement *next = nowCategory->first;
  while(next != NULL){
    if(i == choice){
      if(next->command){
        printf("\n");
        execCategoryCommand(next->command->command);
        printf("\n");
      }
      if(next->under){
        nowCategory = next->under;
      }
      return nowCategory;
    }
    i++;
    next = next->next;
  }
  return nowCategory->parent->above;
}

int execCategoryCommand(char *command){
  char cmd[COMMAND_LENGTH] = {'\0'};
  strcpy(cmd,command);
  char param = getNextCategoryParam(cmd);
  while(param != -1){
    askForCategoryPram(cmd,param);
    param = getNextCategoryParam(cmd);
  }
  printf("Execution de la commande : %s\n",cmd);
  //execCommandSync(cmd);
}

void askForCategoryPram(char* command,char paramType){
  switch(paramType){
    case 'd':
      printf("Number> ");
    break;
    case 's':
      printf("String> ");
    break;
    default:
      printf("Parameter> ");
    break;
  }
  //Séparation de la chaine
  char end[COMMAND_LENGTH];
  int capture = 0;
  int i,j;
  for(i = 0,j = 0; i<strlen(command); i++){
    if(command[i] == '%' && (command[i+1]>=97 && command[i+1]<=122)){
      capture = i;
      i += 2;
    }
    if(capture != 0){
      end[j] = command[i];
      j++;
    }
  }
  command[capture] = '\0';
  //Recuperation du paramètre
  char buffer[COMMAND_LENGTH];
  getKeyboard(buffer,COMMAND_LENGTH);
  switch(paramType){
    case 'd':
      strcat(command,buffer);
    break;
    case 's': default:
      strcat(command,buffer);
    break;
  }
  strcat(command,end);
}

char getNextCategoryParam(char *command){
  int i;
  for(i = 0; i<strlen(command); i++){
    if(command[i] == '%' && (command[i+1]>=97 && command[i+1]<=122)){
      return command[i+1];
    }
  }
  return -1;
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
        char *params = getCategoryParams(buffer);
        if(params != NULL){
          strcpy(newCommand->parameters,params);
          free(params);
        }
        lastElement->command = newCommand;
      }
    } else if(deep > baseDeep) {
      lastElement->under = parseCategory(file,lastPosition,NULL);
      lastElement->under->parent = lastElement;
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
  element->above = parent;
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
  for(i = 0;buffer[i] != '|' && i<strlen(buffer);i++){
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

char* getCategoryParams(char* buffer){
  int finded = 0;
  int i,j = 0;
  char *result = NULL;
  for(i = 0;i<strlen(buffer);i++){
    if(buffer[i] == '|' && finded != 1){
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
      if(next->command->parameters != NULL){
        printf("\t%s",next->command->parameters);
      }
    }
    printf("\n");
    if(next->under != NULL){
      printCategoryTree(next->under,deep+1);
    }
    next = next->next;
  }
}
