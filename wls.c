#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include "color.h"
#include "wls.h"

#define WLS_F_REG 0
#define WLS_F_DIR 1
#define WLS_F_FIFO 2
#define WLS_F_SOCK 3
#define WLS_F_CHR 4
#define WLS_F_BLK 5
#define WLS_F_LNK 10

#define WLS_F_EXE 6
#define WLS_F_SRC 7
#define WLS_F_MUC 8
#define WLS_F_IMG 9

struct dirent** getFolderContent(DIR *folder);
void printDir(struct dirent **elements);
int getType(struct dirent *element);
char* getExtention(struct dirent *element);
char *getColor(struct dirent *element);
int isExe(struct dirent *element);
int isSrc(struct dirent *element);
int isMus(struct dirent *element);
int isImg(struct dirent *element);
char* getExtention(struct dirent *element);
void reverseOrder(struct dirent **elements);

//fonction listant le contenu d'un dossier
//Paramètres :
//  path : chemin du dossier a afficher (relatif/absolu)
//Renvoie : 0 si le dossier n'a pas pu etre ouvert et 1 si tout c'est bien passé
int wls(char *path,int parameter){
  //On ouvre le dossier demandé
  DIR *folder = NULL;
  folder = opendir(path);
  if(folder == NULL){
    //Si il y a un erreur on renvoie 0;
    return 0;
  }
  //On lis le contenu du repertoire
  struct dirent **elements = getFolderContent(folder);
  //On inverse le resultat
  if(parameter == WLS_NORDER)
  reverseOrder(elements);
  //On affiche le resultat
  printDir(elements);
  return 1;
}

//Fonction recupèrant le contenu du dossier donné sous forme d'un tableau de structure dirent
//Paramètres :
//  folder : structure DIR du dossier a ouvrir
//Renvoie : un tableau de structure dirent
struct dirent** getFolderContent(DIR *folder){
  //Variable de l'element actuel
  struct dirent *element;
  //Variable du tableau global
  struct dirent **result = NULL;
  //Taille du tableau global
  int length = 0;
  //Pour chaque element du dossier
  while((element = readdir(folder)) != NULL){
    //On realloc le tableau global
    result = realloc(result, sizeof (struct dirent*) * (++length+1));
    //Ajoute l'élément
    result[length-1] = element;
  }
  //Fini par NULL
  result[length] = NULL;
  //Fin de la fonction
  return result;
}

//Afficher le dossier a l'ecran (avec couleurs)
//Paramètres :
//  elements : tableau de structures dirent
void printDir(struct dirent **elements){
  struct dirent *next = elements[0];
  int i;
  for(i = 1;next != NULL;i++){
    char *color = getColor(next);
    printf("%s%s\n" COLOR_RESET, color,next->d_name);
    next = elements[i];
  }
}

//Fonction permettant de recupèrer la couleur d'un fichier
//Paramètres :
//  element : structure dirent de l'élément
//Renvoie : une chaine de caractères decrivant la couleur de forme AINSI
char *getColor(struct dirent *element){
  switch(getType(element)){
    case WLS_F_REG :
      return COLOR_RESET;
      break;
    case WLS_F_DIR :
      return COLOR_YELLOW;
      break;
    case WLS_F_FIFO :
      return COLOR_BLUE;
      break;
    case WLS_F_SOCK :
      return COLOR_RESET;
      break;
    case WLS_F_CHR :
      return COLOR_RESET;
      break;
    case WLS_F_BLK :
      return COLOR_RED;
      break;
    case WLS_F_LNK :
      return COLOR_BLUE;
      break;
    case WLS_F_EXE :
      return COLOR_CYAN;
      break;
    case WLS_F_SRC :
      return COLOR_MAGENTA;
      break;
    case WLS_F_MUC :
      return COLOR_RED;
      break;
    case WLS_F_IMG :
      return COLOR_GREEN;
      break;
  }
}

//Recupère le type de fichier d'un élément dirent
//Paramètres :
//  element : l'element dirent
//Renvoie : Le type de fichier
int getType(struct dirent *element){
  switch(element->d_type){
    case DT_DIR:
      return WLS_F_DIR;
      break;
    case DT_FIFO:
      return WLS_F_FIFO;
      break;
    case DT_SOCK:
      return WLS_F_SOCK;
      break;
    case DT_CHR:
      return WLS_F_CHR;
      break;
    case DT_BLK:
      return WLS_F_CHR;
      break;
    case DT_LNK:
      return WLS_F_LNK;
      break;
    case DT_REG: case DT_UNKNOWN: default:
      if(isExe(element) == 1){
        return WLS_F_EXE;
      } else if(isSrc(element) == 1){
        return WLS_F_SRC;
      } else if(isMus(element) == 1){
        return WLS_F_MUC;
      } else if(isImg(element) == 1){
        return WLS_F_IMG;
      }  else {
        return WLS_F_REG;
      }
      break;
  }
}

//Verifie qau'un element dirent est un executable
//Paramètres :
//  element : l'element dirent
//Renvoie : 1 si oui 0 si non
int isExe(struct dirent *element){
  char *extention = getExtention(element);
  if(extention == NULL)
    return 0;
  if(strcmp(extention,"out") == 0 || strcmp(extention,"exe") == 0 || strcmp(extention,"exe") == 0){
    free(extention);
    return 1;
  }else{
    free(extention);
    return 0;
  }
}

//fonction permettant de verifier qu'un element dirent est un fichier source
//Paramètres :
//  element : element dirent
//Renvoie : 1 si oui ou 0 si non
int isSrc(struct dirent *element){
  char *extention = getExtention(element);
  if(extention == NULL)
    return 0;
  if(strcmp(extention,"c") == 0 || strcmp(extention,"cpp") == 0 || strcmp(extention,"py") == 0 || strcmp(extention,"js") == 0 || strcmp(extention,"java") == 0){
    free(extention);
    return 1;
  }else{
    free(extention);
    return 0;
  }
}

//Fonction permettant de verifier qu'un fichier est un fichier musique
//Paramètres :
//  element : l'element a analyser
//Renvoie : 1 si oui ou 0 si non
int isMus(struct dirent *element){
  char *extention = getExtention(element);
  if(extention == NULL)
    return 0;
  if(strcmp(extention,"mp3") == 0 || strcmp(extention,"aac") == 0 || strcmp(extention,"mp4") == 0 || strcmp(extention,"flac") == 0 || strcmp(extention,"midi") == 0){
    free(extention);
    return 1;
  }else{
    free(extention);
    return 0;
  }
}

//Fonction verifiant que la structure dirent est un fichier musique
//Paramètres :
//  element : l'element dirent
//Renvoie : 1 si oui 0 si non
int isImg(struct dirent *element){
  char *extention = getExtention(element);
  if(extention == NULL)
    return 0;
  if(strcmp(extention,"jpg") == 0 || strcmp(extention,"png") == 0 || strcmp(extention,"gif") == 0 || strcmp(extention,"bmp") == 0 || strcmp(extention,"jpeg") == 0){
    free(extention);
    return 1;
  }else{
    free(extention);
    return 0;
  }
}

//Fonction définissant l'extention d'un fichier
//Paramètres :
//  element : l'element dirent
//Renvoie : une chaine de caractères définissant l'extention
char* getExtention(struct dirent *element){
  //Définis la position du dernier point sur le nom
  int pointPos = -1;
  int i;
  for(i = strlen(element->d_name)-1;i>=0;i--){
    if(element->d_name[i] == '.'){
      pointPos = i;
      break;
    }
  }
  if(pointPos == -1){
    return NULL;
  }
  //Creation d'un chaine contenant l'extention
  char *extention = malloc(sizeof(char)*(strlen(element->d_name)-i));
  int j;
  for(i = pointPos+1, j = 0; i<strlen(element->d_name); i++){
    extention[j] = element->d_name[i];
    j++;
  }
  extention[j] = '\0';
  return extention;
}

//Inverse l'ordre original d'un tableau
//Paramètres :
// elements : tableau d'elements dirents a inverser
void reverseOrder(struct dirent **elements){
  struct dirent **temp = NULL;
  struct dirent *next = elements[0];
  int i;
  //Transfert dans le tableau temporaire
  for(i=1;next != NULL;i++){
    temp = realloc(temp, sizeof(struct dirent*)*(i+1));
    temp[i-1] = next;
    next = elements[i];
  }
  //Retransmission dans le premier tableau
  int j;
  for(i=i-2,j=0;i>=0;i--){
    elements[j] = temp[i];
    j++;
  }
  free(temp);
}
