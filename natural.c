#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exec.h"
#include "config.h"
#include "display.h"
#include "natural.h"
#include "color.h"

char** strSlice(char *str,char *separator);
char* getCommandLine(char *locale,char *line);
char* strReplace(char *str,char *insert,char replacement);
int containNumber(char **words);

int initNaturalMode(Config *configuration){
  while(1){
    printPrompt(configuration->prompt);
    printf(COLOR_GREEN "%s\n" COLOR_RESET,toLocaleString(configuration->lang,"natural.prompt"));
    char buffer[COMMAND_LENGTH] = {'\0'};
    char comd[COMMAND_LENGTH];
    getKeyboard(buffer,COMMAND_LENGTH);
    char *command = getCommandLine(configuration->locale,buffer);
    if(command == NULL){
      printf(COLOR_RED "%s\n" COLOR_RESET,toLocaleString(configuration->lang,"natural.notFound"));
    } else {
      int result = execCommandSync(command,configuration);
      if(result == 0){
        printf(COLOR_RED "%s" COLOR_RESET " %s\n",toLocaleString(configuration->lang,"error.error"),toLocaleString(configuration->lang,"error.programError"));
      }
    }
    free(command);
  }
  return EXIT_SUCCESS;
}

char* getCommandLine(char *locale,char *line){
  //Chargement du fichier de mot clefs
  char locPath[COMMAND_LENGTH] = {'\0'};
  strcat(locPath,NATURAL_PATH);
  strcat(locPath,locale);
  FILE *keywordsFile = NULL;
  keywordsFile = fopen(locPath,"r");
  if(keywordsFile == NULL)
    return NULL;
  //Division de la ligne en tableau séparent les espaces
  char **words = strSlice(line," ");
  //Recherche des mots clefs
  char fileLine[COMMAND_LENGTH];
  while(fgets(fileLine,COMMAND_LENGTH,keywordsFile)!=NULL){
    //Suppression du \n final
    strcpy(fileLine,strtok(fileLine,"\r"));
    int k;
    for(k = 0; fileLine[k] != '\r' && fileLine[k] != '\n' && k<strlen(fileLine); k++){}
    fileLine[k] = '\0';
    //Analyse de la ligne
    char **lineSpects = strSlice(fileLine,"|");
    char **keywords = strSlice(lineSpects[0],",");
    char *next = words[0];
    int i,j;
    for(i=1,j=0;next != NULL && keywords[j] != NULL;i++){
      if(strcmp(next,keywords[j]) == 0){
        j++;
      }
      next = words[i];
    }
    if(keywords[j] == NULL){
      char *result = malloc(sizeof(char)*strlen(lineSpects[1]));
      strcpy(result, lineSpects[1]);
      if(lineSpects[2] == NULL){
        //Si aucun parametres d'est demandé
        free(keywords);
        free(lineSpects);
        return result;
      }else{
        //Si des paramètres sont requis
        if(strcmp(lineSpects[2],"directory") == 0){
          int indexDirectory = containDirectory(words);
          if(indexDirectory>=0){
            return strReplace(result,words[indexDirectory],'%');
          }
        }else if(strcmp(lineSpects[2],"file") == 0){

        }else if(strcmp(lineSpects[2],"number") == 0){
          int indexNumber = containNumber(words);
          if(indexNumber>=0){
            return strReplace(result,words[indexNumber],'%');
          }
        }
      }
    }
    free(keywords);
    free(lineSpects);
  }
  free(words);
  return NULL;
}

char** strSlice(char *str,char *separator){
  int length = 0;
  char **result = NULL;
  //Séparation
  char *p    = strtok(str, separator);
  while (p) {
    result = realloc(result, sizeof (char*) * (++length+1));
    result[length-1] = p;
    p = strtok (NULL,separator);
  }
  result[length] = NULL;
  return result;
}

int containDirectory(char **words){
  int i;
  char *next = words[0];
  for(i=1;next != NULL;i++){
    if(next[0] == '/' || (next[0] == '.' && next[1] == '/')){
      return i-1;
    }
    next = words[i];
  }
  return -1;
}

int containNumber(char **words){
  int i;
  char *next = words[0];
  for(i=1;next != NULL;i++){
    int j;
    for(j=0;j<strlen(next) && (next[j] >= 48 && next[j] <= 57);j++){
      if(j == strlen(next)-1){
        return i-1;
      }
    }
    next = words[i];
  }
  return -1;
}

char* strReplace(char *str,char *insert,char replacement){
  int i,j, captur = -1;
  char end[COMMAND_LENGTH] = {'\0'};
  char *start = malloc(sizeof(char)*COMMAND_LENGTH);
  strcpy(start,str);
  for(i=0,j=0;i<strlen(start);i++){
    if(captur != -1){
      end[j] = start[i];
      j++;
    } else if(start[i] == replacement){
      captur = i;
    }
  }
  end[j] = '\0';
  start[captur] = '\0';
  strcat(start,insert);
  strcat(start,end);
  return start;
}
