#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/mount.h>

int main()
{
   const char* src  = "none";
   const char* target = "/var/tmp"; /* /var/tmp = stockage de fichiers temporaires */
   const char* type = "tmpfs"; /* tmpfs est le nom donné au système de fichier Unix temporaire */
   const unsigned long mntflags = 1;
   const char* opts = "mode=0700,uid=65534";   /* 65534 est l'UID de personne, 0700 = mode répertoire */

   int result = mount(src, target, type, mntflags, opts);

   if (result == 0)
   {
      return 1;
   }
   else
   {
      printf("Erreur : montage impossible %s\n"
             "Raison: %s [%d]\n",
             src, strerror(errno), errno);
      return -1;
   }

   return 0;
}
