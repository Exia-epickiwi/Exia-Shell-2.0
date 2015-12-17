#include <stdio.h>
#include <stdlib.h>
#include "language.h"
#include "config.h"
#include "color.h"
#include "exec.h"
#include "hanoi.h"

#define TOWER_NUMBER 3

HanoiTower* createHanoiTower();
HanoiDisc* createHanoiDisc(int size);
HanoiTower* addHanoiDisc(HanoiTower* tower, HanoiDisc* disc);
HanoiTower* fillHanoiTower(HanoiTower* tower,int startSize,int endSize);
void printHanoiTowers(HanoiTower *towers[],int towerNumber, int maxHeight);
void printDisc(int size,int maxSize);
HanoiDisc* getHanoiDisc(HanoiTower *tower,int index);
HanoiDisc* removeHanoiDisc(HanoiTower *tower);
int moveHanoiDisc(HanoiTower *from, HanoiTower *to);
void startGame(Config *config,int discNumber);
void saveScore(char *name, int scoreTime, int level, int score);

//Démarrage du jeu de hanoi
//Paramètres :
//  config : Structure de configuration pour la langue
void initHanoiGame(Config *config){
  //Affichage du nom et des regles
  printf("%s\n",toLocaleString(config->lang,"hanoi.name"));
  printf("%s\n",toLocaleString(config->lang,"hanoi.rules"));
  //On demande le nombre de disques
  char enterDiff[5];
  int discNumber = 0;
  int maxDisc = 10;
  do{
    printf("%s (3-%d) : ",toLocaleString(config->lang,"hanoi.askDisc"),maxDisc);
    getKeyboard(enterDiff,5);
    discNumber = atoi(enterDiff);
  }while(discNumber<3 || discNumber>maxDisc);
  //On démarre le jeu
  startGame(config,discNumber);
}

void startGame(Config *config, int discNumber){
  //Creation des trois tours avec le nombre requis de disques
  HanoiTower* towers[TOWER_NUMBER];
  int i;
  for(i=0;i<TOWER_NUMBER;i++){
    towers[i] = createHanoiTower();
  }
  //Remplissage de le première
  fillHanoiTower(towers[0],1,discNumber);
  //Affichage
  printHanoiTowers(towers,TOWER_NUMBER,discNumber);
  printf("\n%s\n",toLocaleString(config->lang,"hanoi.moveInstructions"));
  //Creation de la variable pour le score
  int score = 0;
  //Demarrage du chrono
  time_t start = time(NULL);
  //Tant que la dernière tour n'est pas complète
  while(towers[TOWER_NUMBER-1]->height < discNumber){
    printf("\n\n");
    printf("%s : ",toLocaleString(config->lang,"hanoi.move"));
    //Recupèration du mouvement a faire
    char move[5];
    getKeyboard(move,5);
    //Ajouter un coup au score
    score++;
    printf("\n");
    //On déduit le mouvement
    int moved = 0;
    int fromId = (move[0] - '0')-1;
    int toId = (move[1] - '0')-1;
    //On verifie la validitée du mouvement
    if((fromId >= 0 && fromId < TOWER_NUMBER) && (toId >= 0 && toId < TOWER_NUMBER))
      moved = moveHanoiDisc(towers[fromId],towers[toId]); // On bouge le disque
    //On réecris les tours dans la console
    printHanoiTowers(towers,TOWER_NUMBER,discNumber);
    //On ecris que le déplacement c'est bien éfféctué ou non
    printf("\n%s %d %s %d\n",toLocaleString(config->lang,"hanoi.moveFrom"),fromId+1,toLocaleString(config->lang,"hanoi.moveTo"),toId+1);
    if(moved == 0){
      printf(COLOR_RED "%s\n" COLOR_RESET,toLocaleString(config->lang,"hanoi.moveError"));
    } else {
      printf(COLOR_GREEN "%s\n" COLOR_RESET,toLocaleString(config->lang,"hanoi.moveSuccess"));
    }
  }
  //Des que la derniere tour est complète
  printf("\n\n%s\n",toLocaleString(config->lang,"hanoi.gameFinished"));
  //On fait la différence entre le temps de depart et le temps actuel
  int scoreTime = time(NULL)-start;
  //On ecris le resultat dans la console puis on sauvegarde le tout dans la console
  printf("%s %ds, %s %d\n",toLocaleString(config->lang,"hanoi.gameDuration"),scoreTime, toLocaleString(config->lang, "hanoi.score"), score);
  saveScore(config->prompt, scoreTime, discNumber, score);
}

//Crée une pile appelée HanoiTower
//Renvoie : un pointeur sur la structure
HanoiTower* createHanoiTower(){
  HanoiTower *tower = malloc(sizeof(HanoiTower));
  tower->top = NULL;
  tower->height = 0;
  return tower;
}

//Crée un élément de la pile HanoiTower appelé HanoiDisc
//Paramètres :
//  size : Taille du disque
//Renvoie : un pointeur sur la structure de disque
HanoiDisc* createHanoiDisc(int size){
  HanoiDisc *disc = malloc(sizeof(HanoiDisc));
  disc->tower = NULL;
  disc->next = NULL;
  disc->size = size;
  return disc;
}

HanoiTower* addHanoiDisc(HanoiTower* tower, HanoiDisc* disc){
  disc->next = tower->top;
  disc->tower = tower;
  tower->top = disc;
  tower->height = tower->height+1;
  return tower;
}

//Remplis une tour avec des disques de tailles croissantes
//Paramètres :
//  tower : tour a remplire
//  startSize : Taille du plus haut disque de la tour
//  endSize : Taille du disque le plus bas de la tour
//Renvoie : le pointeur de la tour donnée en paramètres
HanoiTower* fillHanoiTower(HanoiTower* tower,int startSize,int endSize){
  int j;
  for(j=endSize;j>=startSize;j--){
    addHanoiDisc(tower,createHanoiDisc(j));
  }
  return tower;
}

//Recupère le disque d'un certain ID
//Paramètres :
//  tower : tour a anlyser
//  index : index en partant du plus haut disque de la tour
//Renvoie : le disque correspondant a l'index ou NULL s'il n'existe pas
HanoiDisc* getHanoiDisc(HanoiTower *tower,int index){
  HanoiDisc *next = tower->top;
  int i;
  for(i=0;next != NULL;i++){
    if(i == index){
      return next;
    }
    next = next->next;
  }
  return NULL;
}

//Supprime un disque d'une tour
//Paramètres :
//  tower : tour dont on doit retirer le disque
//Renvoie : un pointeur sur le disque retiré ou NULL s'il n'y a rien a retirer
HanoiDisc* removeHanoiDisc(HanoiTower *tower){
  if(tower->top != NULL){
    HanoiDisc *disc = tower->top;
    tower->top = disc->next;
    disc->next = NULL;
    disc->tower = NULL;
    tower->height = tower->height-1;
    return disc;
  } else {
    return NULL;
  }
}

//Fonction déplaceant un disque d'une tour a l'autre
//Paramètres :
//  from : Tour de départie
//  to : Tour d'arrivée
//Renvoie : 1 si tout c'est bien passé ou 0 si non
int moveHanoiDisc(HanoiTower *from, HanoiTower *to){
  if(from->top != NULL){
    if(to->top == NULL || (to->top->size > from->top->size)){
      HanoiDisc *disc = removeHanoiDisc(from);
      addHanoiDisc(to,disc);
      return 1;
    }
  }
  return 0;
}

//Affiche le contenu des tours
//Paramètres :
//  towers : les tours a afficher
//  towerNumber : Le nombre de tours a afficher
//  maxHeight : Taille maximale d'une tour
void printHanoiTowers(HanoiTower *towers[],int towerNumber, int maxHeight){
  //Pour chaque etage
  int i;
  for(i=0;i<maxHeight;i++){
    //Pour chaque tour
    int j;
    for(j=0;j<towerNumber;j++){
      if(i<maxHeight-towers[j]->height){
        printDisc(0,maxHeight);
      } else {
        HanoiDisc *disc = getHanoiDisc(towers[j],i-(maxHeight-towers[j]->height));
        if( disc != NULL){
          printDisc(disc->size,maxHeight);
        } else {
          printDisc(0,maxHeight);
        }
      }
      printf("\t");
    }
    //---
    printf("\n");
  }
  //---
  int j;
  for(j=0;j<towerNumber;j++){
    for(i=0;i<maxHeight;i++){
      printf(" ");
    }
    printf("%d",j+1);
    for(i=0;i<maxHeight;i++){
        printf(" ");
    }
    printf("\t");
  }
  printf("\n");
}

//Affiche un disuqe d'une tour
//Paramètres :
//  size : Taille du disque
//  maxSize : Taille maximale d'un disque
void printDisc(int size,int maxSize){
    switch(size%6){
      case 0:
        printf(COLOR_BLUE);
      break;
      case 1:
        printf(COLOR_CYAN);
      break;
      case 2:
        printf(COLOR_GREEN);
      break;
      case 3:
        printf(COLOR_MAGENTA);
      break;
      case 4:
        printf(COLOR_YELLOW);
      break;
      case 5:
        printf(COLOR_RED);
      break;
    }
    int i;
    for(i=0;i<maxSize;i++){
      if(i<maxSize-size){
        printf(" ");
      } else {
        printf("%d",size%10);
      }
    }
    printf("|");
    for(i=0;i<maxSize;i++){
      if(i>size-1){
        printf(" ");
      } else {
        printf("%d",size%10);
      }
    }
    printf(COLOR_RESET);
}

//Sauvegarde le score du joueur
//Paramètres :
//  name : Nom du fichier ou sauvegarde
//  scoreTime : temps en secondes qu'a duré le jeu
//  level : Niveau de difficulté (nombre de disques) du jeu
//  score : Nombre de coups a sauvegarder
void saveScore(char *name, int scoreTime, int level, int score){
  FILE *file = fopen(PATH_SCORE, "r+");
  char scor[50];
  sprintf(scor, "[%d] %d-%d - %s\n", level, scoreTime, score, name);
  if(file == NULL){
    file = fopen(PATH_SCORE, "w");
    fputs(scor, file);
  } else {
    fseek(file, 0, SEEK_END);
    fputs(scor, file);
  }
  fclose(file);
}
