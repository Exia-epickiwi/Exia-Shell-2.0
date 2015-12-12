#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expert.h"
#include "display.h"
#include "exec.h"
#include "exec.c"
#include "config.h"

int initExpertMode(Config *configuration) {
  char commande[256];
  do {

    printPrompt(configuration->prompt);
    if(getKeyboard(commande, 256) == 0) return 0;

    if(strcmp(commande, "exit") == 0) break;

    printf("%d\n",execCommand(commande));
  }while(1);
 return 0;
}
