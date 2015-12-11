#include <stdlib.h>
#include "language.h"

Language* loadLanguage(char *file){
  //On charge le fichier donné en paramètres
  FILE *langFile = fopen(file,"r");
  //Verification de l'existance du fichier
  if(langFile == NULL){
    return NULL;
  }

  char line[MAX_LANG_LINE_LENGTH] = "";
  while(fgets(line,MAX_LANG_LINE_LENGTH,langFile)){
    printf("Ligne : %s",line);
  }

}
