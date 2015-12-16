#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "wpwd.h"

void getPwd() {
    char cwd[1025];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}
