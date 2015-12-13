#include <stdio.h>
#include <stdlib.h>
#include "language.h"
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

void initHanoiGame(Language *lang){
  //Creation des trois tours avec le nombre requis de disques
  HanoiTower* towers[TOWER_NUMBER];
  int discNumber = 5;
  int i;
  for(i=0;i<TOWER_NUMBER;i++){
    towers[i] = createHanoiTower();
  }
  fillHanoiTower(towers[0],1,discNumber);
  printHanoiTowers(towers,TOWER_NUMBER,discNumber);
  printf("\n%s\n",toLocaleString(lang,"hanoi.moveInstructions"));
  while(towers[TOWER_NUMBER-1]->height < discNumber){
    printf("\n\n");
    printf("%s : ",toLocaleString(lang,"hanoi.move"));
    char move[5];
    getKeyboard(move,5);
    printf("\n");
    int moved = 0;
    int fromId = (move[0] - '0')-1;
    int toId = (move[1] - '0')-1;
    if((fromId >= 0 && fromId < TOWER_NUMBER) && (toId >= 0 && toId < TOWER_NUMBER))
      moved = moveHanoiDisc(towers[fromId],towers[toId]);
    printHanoiTowers(towers,TOWER_NUMBER,discNumber);
    printf("\n%s %d %s %d\n",toLocaleString(lang,"hanoi.moveFrom"),fromId+1,toLocaleString(lang,"hanoi.moveTo"),toId+1);
    if(moved == 0){
      printf(COLOR_RED "%s\n" COLOR_RESET,toLocaleString(lang,"hanoi.moveError"));
    } else {
      printf(COLOR_GREEN "%s\n" COLOR_RESET,toLocaleString(lang,"hanoi.moveSuccess"));
    }
  }
}

HanoiTower* createHanoiTower(){
  HanoiTower *tower = malloc(sizeof(HanoiTower));
  tower->top = NULL;
  tower->height = 0;
  return tower;
}

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

HanoiTower* fillHanoiTower(HanoiTower* tower,int startSize,int endSize){
  int j;
  for(j=endSize;j>=startSize;j--){
    addHanoiDisc(tower,createHanoiDisc(j));
  }
  return tower;
}

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
