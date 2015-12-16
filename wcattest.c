#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void usage(char **av)
{
        printf("Usage: %s [FILES] ...\n", av[0]);
}

int principal (int ac, char **av)
{
        int i, fd;
        ssize_t byte_lu;
        char buffer[1024];

        if (ac < 2)
                usage(av);

        for (i=1; i<ac; i++)
        {
                fd = open(av[i],O_RDONLY);

                if (fd == -1)
                        perror("open: ");
                else
                {
                        while((byte_lu=read(fd,buffer, sizeof(buffer))))
                                write(STDOUT_FILENO, buffer, byte_lu);

                        close(fd);
                }
        }

        return 0;
}
