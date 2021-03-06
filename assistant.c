#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "color.h"
#include "config.h"
#include "config.h"
#include "assistant.h"
#include "display.h"
#include "exec.h"
#include "log.h"
#include "language.h"

Category* parseCategory(FILE *file,long position,Category *parent);
Category* loadCategories(char *path);
int getDeep(char *buffer);
void addCategoryElement(Category *parent,char *name,Category *under, CategoryCommand *command);
char* getCategoryLineName(char* buffer);
char* getCategoryCommand(char* buffer);
int printCategoryElements(Config *config,Category *cat);
Category* performCategoryAction(Config *config,Category *nowCategory,char *input,int maxChoice);
int execCategoryCommand(Config *config,CategoryCommand *command);
char getNextCategoryParam(char *command);
void askForCategoryPram(Config *config,char* command,char paramType,char *pramsNames);
char* getCategoryParams(char* buffer);

//Fonction démarrant le mode assistant
//Paramètres :
//Config : structure config contenant la configuration
//Renvoie : Le code d'arrêt du programme
int initAssistantMode(Config *config){
  Category *index = loadCategories(PATH_ASSISTANT);
  if(index == NULL){
    printf("%s %s\n",toLocaleString(config->lang,"error.error"),toLocaleString(config->lang,"error.loadCategories"));
    exit(EXIT_FAILURE);
  }
  Category *displayed = index;
  while(1){
    printPrompt(config->prompt);
    if(index == displayed){
      printf("%s\n", toLocaleString(config->lang,"assistant.indexPrompt"));
    } else {
      printf("%s\n", toLocaleString(config->lang,displayed->parent->name));
    }
    int maxChoice = printCategoryElements(config,displayed);
    printf("%s (1-%d) : ",toLocaleString(config->lang,"assistant.promptChoice"),maxChoice);
    char buffer[5] = {'\0'};
    getKeyboard(buffer,5);
    displayed = performCategoryAction(config,displayed,buffer,maxChoice);
  }
}

//Affiche les éléments d'une catégorie
//Paramètres :
//Lang : structure de langue
//Cat : structure catégorie a afficher
//Renvoie : le dernier numéro de la liste
int printCategoryElements(Config *config,Category *cat){
  CategoryElement *next = cat->first;
  int i = 1;
  while(next != NULL){
    printf("%d - %s\n",i,toLocaleString(config->lang,next->name));
    i++;
    next = next->next;
  }
  if(cat->parent != NULL){
    printf("%d - %s\n",i,toLocaleString(config->lang,"assistant.back"));
  } else {
    i--;
  }
  return i;
}

//Exécute une action en fonction de ce que demande l'utilisateur
//Paramètres :
//Lang : structure de langue
//NowCategory : catégorie actuellement visionnée
//Input : ce qu'a entré l'utilisateur
//MaxInput : dernier numero de la liste d'elements affchés
//Renvoie : la nouvelle catégorie à afficher
Category* performCategoryAction(Config *config,Category *nowCategory,char *input,int maxInput){
  int choice = atoi(input);
  if(choice == 0){
    printf(COLOR_RED "\n%s" COLOR_RESET " %s\n",toLocaleString(config->lang,"error.error"),toLocaleString(config->lang,"error.assistant.unknownChoice"));
    return nowCategory;
  } else if(choice > maxInput || choice < 1){
    printf(COLOR_RED "\n%s" COLOR_RESET " %s\n",toLocaleString(config->lang,"error.error"),toLocaleString(config->lang,"error.assistant.outChoice"));
    return nowCategory;
  }
  int i = 1;
  CategoryElement *next = nowCategory->first;
  printf("\n");
  while(next != NULL){
    if(i == choice){
      if(next->command){
        int success = execCategoryCommand(config, next->command);
        if(success == 0){
          printf(COLOR_RED "%s" COLOR_RESET " %s\n",toLocaleString(config->lang,"error.error"),toLocaleString(config->lang,"error.programError"));
        }
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

//Exécuter une commande utilisateur en lui demandant les paramètres
//Paramètres :
//Lang : Structure de langu
//Command : structure CategoryCommand contenant les informations de commande
//Renvoie : 0 si cela a marché 1 si non
int execCategoryCommand(Config *config,CategoryCommand *command){
  char cmd[COMMAND_LENGTH] = {'\0'};
  strcpy(cmd,command->command);
  char parameters[COMMAND_LENGTH] = {'\0'};
  strcpy(parameters,command->parameters);
  char param = getNextCategoryParam(cmd);
  while(param != -1){
    askForCategoryPram(config,cmd,param,parameters);
    param = getNextCategoryParam(cmd);
  }
  int pid = execCommandSync(cmd, config);
  toLog(cmd);
  return pid;
}

//Demande un paramètre a l'utilisateur
//Paramètres :
//Lang : structure de langue
//Command : commande a executer
//ParamType : type de paramètre
//ParamsNames : liste de paramètres formatés
void askForCategoryPram(Config *config,char* command,char paramType,char *paramsNames){
  char param[COMMAND_LENGTH] = {'\0'};
  if(paramsNames != NULL){
    int k;
    for(k = 0;paramsNames[k] != '|' && k<strlen(paramsNames);k++){
      param[k] = paramsNames[k];
    }
    param[k] = '\0';
    int l;
    for(l = 0,k++;k<strlen(paramsNames);k++){
      paramsNames[l] = paramsNames[k];
      l++;
    }
    paramsNames[l] = '\0';
    printf("%s : ",toLocaleString(config->lang,param));
  } else {
    printf("> ");
  }
  //Séparation de la chaine
  char end[COMMAND_LENGTH];
  int capture = 0;
  int i,j;
  for(i = 0,j = 0; i<strlen(command); i++){
    if(capture == 0 && command[i] == '%' && (command[i+1]>=97 && command[i+1]<=122)){
      capture = i;
      i += 2;
    }
    if(capture != 0){
      end[j] = command[i];
      j++;
    }
  }
  command[capture] = '\0';
  end[j] = '\0';
  //Récuperation du paramètre
  char buffer[COMMAND_LENGTH];
  getKeyboard(buffer,COMMAND_LENGTH);
  strcat(command,buffer);
  strcat(command,end);
}

//Récupère le prochain paramètre a remplire
//Paramètres :
//Command : commande a exécuter
//Renvoie : le type de paramètre -1 si aucun paramètre n'est requis
char getNextCategoryParam(char *command){
  int i;
  for(i = 0; i<strlen(command); i++){
    if(command[i] == '%' && (command[i+1]>=97 && command[i+1]<=122)){
      return command[i+1];
    }
  }
  return -1;
}

//Charge les catégories
//Paramètres :
//Path : chemin du fichier où charger les catégories
Category* loadCategories(char *path){
  //Ouvrir un fichier
  FILE *categoryFile = fopen(path,"r");
  //Si il y a erreur
  if(categoryFile == NULL)
    return NULL;
  //Lecture de chaque ligne
  return parseCategory(categoryFile,ftell(categoryFile),NULL);
  //Fermeture du fichier
  fclose(categoryFile);
}

//Parse les catégories en une structure en arbre
//Paramètres :
//File : structure FILE décrivant le fichier ouvert
Category* parseCategory(FILE *file,long position,Category *parent){
  //On place le curseur a la position donnée
  fseek(file,position,SEEK_SET);
  //Buffer de caracteres
  char buffer[MAX_CATEGORY_LINE_LENGTH];
  //Chargement de la première ligne
  fgets(buffer,MAX_CATEGORY_LINE_LENGTH,file);
  //Calcul de la profondeur
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
    int k;
    for(k = 0; buffer[k] != '\r' && buffer[k] != '\n' && k<strlen(buffer); k++){}
    buffer[k] = '\0';
    //Vérification que l'on est toujours soit au dessus soit au même niveau
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

//Calcul la profondeur d'une ligne dans l'arbre
//Paramètres :
//Buffer : ligne à mesurer
//Renvoie : La profondeur
int getDeep(char *buffer){
  int deep = 0;
  while (buffer[deep]==' ') {
    deep++;
  }
  return deep;
}

//Ajout un élément à une catégorie
//Paramètres :
//Parent : catégorie contenant le tout
//Name : nom de l'élément
//Under : éventuelle sous-catégorie
//Command : éventuelle commande à executer si choisi
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

//Récupère le nom de l'élément à partir d'une chaîne
//Paramètres :
//Buffer : ligne à mesurer
//Renvoie : le nom de l'element
char* getCategoryLineName(char* buffer){
  char *result = malloc(sizeof(char)*COMMAND_LENGTH);
  int i,j = 0;
  for(i = 0;buffer[i] != ':' && i<strlen(buffer);i++){
    if(buffer[i] != ' '){
      result[j] = buffer[i];
      j++;
    }
  }
  result[j] = '\0';
  return result;
}

//Récupère la commande à exécuter à partir d'une chaîne
//Paramètres :
//Buffer : ligne à mesurer
//Renvoie : la commande a exécuter
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
    result[j] = '\0';
    return result;
  }else{
    return NULL;
  }
}

//Récupère les paramètres à partir d'une chaîne
//Paramètres :
//Buffer : ligne à mesurer
//Renvoie : les paramètres de la commande
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
    result[j] = '\0';
    return result;
  }else{
    return NULL;
  }
}

//Affiche un arbre des différentes catégories
//Paramètres :
//Index : Catégorie de base
//Deep : profondeur de base
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
