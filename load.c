#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "load.h"

int loadConfig(){ //Fonction permettant de charger des variables à partir d'un dossier
  int mode;
  char language[3];
  char prompt[256];

  int idFichierConfig = -1;
  idFichierConfig = open("config.txt", O_RDONLY); //ouvre le fichier en lecture seul

  if(idFichierConfig == -1){
    idFichierConfig = open("config.txt", O_CREAT | O_WRONLY, 0777);
    write(idFichierConfig, "mode : 0\nlanguage : fr\nname : exsh\n", 35);
    mode = 0;
    language = "Fr";
    prompt = "exsh";
  } else {
    
  }

  close(idFichierConfig);
  return 1; //retourne 1 si tout est chargé correctement
}
