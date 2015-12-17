#include <unistd.h>

//Fonction permettant de changer le dossier de travail du shell
//Paramètres :
//Path : Chemin relatif ou absolu du fichier
//Renvoie : 0 en cas de changement reussi, ou -1 en cas d’erreur
int changeWorkingDirectory(char *path){
  return chdir(path);
}
