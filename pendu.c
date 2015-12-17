#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "color.h"
#include "config.h"
#include "display.h"

char *motCached(int *letterFind, char *motSearch);
int searchIndex(char *motSearch, char letter, int i);
int compare(char *txt1, char *txt2);

void initPenduGame(Config *config){
  int maxScore = 20, score = 0;
  char motSearch[] = "appartement";
  int *letterFind = calloc(sizeof(motSearch), sizeof(int));
  int index = 0;
  do{
    printf("Il vous reste %d coups possible\n", maxScore);
    printf("Le mot à découvrire : %s\n>", motCached(letterFind, motSearch));
    char *enter = calloc(sizeof(motSearch), sizeof(char));
    if(getKeyboard(enter, sizeof(motSearch)) == 1){
      if(enter[1] == '\0'){
        int letter = searchIndex(motSearch, enter[0], 0);
        while(letter != -1){
          letterFind[letter] = 1;
          letter = searchIndex(motSearch, enter[0], letter+1);
          score++;
        }

      } else {
        if(compare(motSearch, enter) == 1){
          score = sizeof(motSearch);printf("Bravo !\n");break;
        }
      }

      maxScore--;
      int i, valid = 1;
      for(i = 0; i < (sizeof(motSearch)-1); i++){
        if(letterFind[i] != 1) valid = 0;
      }
      if(valid == 1) break;
    }
    free(enter);
  }while(maxScore != 0);
  printf("Score : %d\nLe mot etait %s\n", score, motSearch);
}
int searchIndex(char *motSearch, char letter, int i){
  int index;
  for(index = i; motSearch[index] != '\0'; index++){
    if(motSearch[index] == letter) return index;
  }
  return -1;
}
int compare(char *txt1, char *txt2){
  int index = 0;
  for(index = 0; txt1[index] != '\0' && txt2[index] != '\0'; index++){
    if(txt1[index] != txt2[index]) return 0;
  }
  if(txt1[index] == '\0' && txt2[index] == '\0') return 1;
  return 0;
}
char *motCached(int *letterFind, char *motSearch){
  char *mixte = calloc(sizeof(motSearch), sizeof(char));
  int index = 0;
  for(index = 0; motSearch[index] != '\0'; index++){
    if(letterFind[index] == 0){
      mixte[index] = '*';
    } else {
      mixte[index] = motSearch[index];
    }
  }
  return mixte;
}
