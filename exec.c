#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include "cd.h"
#include "exec.h"
#include "config.h"
#include "hanoi.h"
#include "color.h"
#include "language.h"
#include "wls.h"
#include "listUser.h"
#include "wpwd.h"
//Fonction executant un programme suivant une commande
//Paramètres :
//  str : Tableau représentant la chaine de caractère de la commande
//Renvoie : le pid du process executé ou -1 si il y a eu une erreur
int execCommand(char *str, Config *config){
  char cmd[255];
  strcpy(cmd,str);
  char **args = NULL;
  int length = 0, i;
  if(strchr(cmd,' ') != NULL){
    char *p    = strtok (cmd, " ");
    while (p) {
      args = realloc(args, sizeof (char*) * (++length+1));
      args[length-1] = p;
      p = strtok (NULL," ");
    }
    args[length] = NULL;
  } else {
    args = malloc(sizeof (char*)*2);
    args[0] = cmd;
    length = 1;
    args[1] = NULL;
  }

  if(strcmp(args[0],"cd") == 0 || strcmp(args[0], "/bin/cd") == 0){
    if(changeWorkingDirectory(args[1])==0){
        return 1;
    }
    return -1;
  } else if(strcmp(args[0],"exit") == 0 || strcmp(args[0], "/bin/exit") == 0){
    exit(0);
  } else if(strcmp(args[0],"history") == 0 || strcmp(args[0], "/bin/history") == 0){
    seeLog(config);
  } else if(strcmp(args[0],"wls") == 0 || strcmp(args[0], "/bin/wls") == 0){
    if(args[1] != NULL && args[2] == NULL && strcmp(args[1],"-r") != 0){
      wls(args[1],WLS_NONE);
    } else if(args[1] != NULL && args[2] != NULL && strcmp(args[2],"-r") == 0){
      wls(args[1],WLS_NORDER);
    } else if(args[1] != NULL && strcmp(args[1],"-r") == 0){
      wls(".",WLS_NORDER);
    } else {
      wls(".",WLS_NONE);
    }
  } else if(strcmp(args[0], "help") == 0 || strcmp(args[0], "/bin/help") == 0){
    char command[255] = {"/usr/bin/man "};
    if(args[1] != NULL) strcat(command, args[1]);
    execCommandSync(command, config);
  } else if(strcmp(args[0], "/bin/ls") == 0){
    char command[255] = {""};
    strcat(command, "ls ");
    int index = 1;
    while(args[index]){strcat(command, args[index]);strcat(command, " "); index++;}
    strcat(command, " --color");
    execCommandSync(command, config);
  } else if(strcmp(args[0], "hanoi") == 0 || strcmp(args[0], "/bin/hanoi") == 0){
    initHanoiGame(config);
  } else if(strcmp(args[0], "setConfig") == 0 || strcmp(args[0], "/bin/setConfig") == 0){
    execCommandSync("sudo /bin/nano /etc/exsh/profile", config);
  } else if(strcmp(args[0], "reboot") == 0 || strcmp(args[0], "/bin/reboot") == 0){
    execCommandSync("clear", config);
    char *argsList[] = {"/bin/exsh", NULL};
    execvp(argsList[0], argsList);
  } else if(strcmp(args[0], "clear") == 0 || strcmp(args[0], "/bin/clear") == 0){
    execCommandSync("/usr/bin/clear", config);
  } else if(strcmp(args[0], "wkill") == 0 || strcmp(args[0], "/bin/wkill") == 0){
    if(kill(atoi(args[1]), SIGQUIT) == -1){
      printf(COLOR_RED "%s" COLOR_RESET, toLocaleString(config->lang, "error.error"));
    }
  } else if(strcmp(args[0], "wpwd") == 0 || strcmp(args[0], "/bin/wpwd") == 0){
    getPwd();
  } else if(strcmp(args[0], "listUser") == 0 || strcmp(args[0], "/bin/listUser") == 0){
    listUser();
  } else {
    int pid = fork();
    if(pid == 0){
      if(execvp(args[0],args) == -1){
        printf(COLOR_RED "%s" COLOR_RESET " %s\n", toLocaleString(config->lang, "error.error"), toLocaleString(config->lang, "error.programError"));
        exit(EXIT_FAILURE);
      }
    }else if(pid < 0){
      free(args);
      return -1;
    }else{
      free(args);
      return pid;
    }
  }
}

//Fonction executant un programme et attendant la fin de clui ci
//Paramètres :
//  str : Tableau représentant la chaine de caractère de la commande
//Renvoie : 1 si tout c'est bien passé si non 0
int execCommandSync(char *command, Config *config){
  int pid = execCommand(command, config);
  if(pid > 0){
    wait(pid);
    return 1;
  } else {
    return 0;
  }
}
