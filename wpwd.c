#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "wpwd.h"
#include "color.h"

//Fonction affichant l'endroit ou se trouve l'utilisateur
void getPwd() {
    char cwd[1025];
    getcwd(cwd, sizeof(cwd));
    printf(COLOR_GREEN "%s\n" COLOR_RESET, cwd);
}
