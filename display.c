#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printPrompt(char *prompt){
  printf("%s>",prompt);
}

int getKeyboard(char *string,int max){
  char *nPos = NULL;
  if(fgets(string,max,stdin) != NULL){
    nPos = strchr(string,'\n');
    if(nPos != NULL){
      *nPos = '\0';
    }
    return 1;
  } else {
    return 0;
  }
}
