#include <stdio.h> 

/* cat : concatène des fichiers */
main(int argc, char *argv[])
{
    FILE *fp;
    void copierfich(FILE *, FILE *);

    if (argc == 1) /* pas d'args : copie l'entrée standard */
        copierfich(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL)    {
                printf("cat : impossible d'ouvrir %s\n", *argv);
                return 1;
            }    else {
                    copierfich(fp, stdout);
                    fclose(fp);
            }
    return 0;
}

/* copierfich : copie le fichier fpe dans le fichier fps */
void copierfich(FILE *fpe, FILE *fps)
{
    int c;

    while ((c = getc(fpe)) != EOF) /* EOF= End Of File*/
        putc(c, fps); /* putc écrit un caractère spécifié sur le flux pointé par le flux */
}
