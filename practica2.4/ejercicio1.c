#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


// Comando: echo 45323 | wc -c

int main(int argc, char**argv){
        int tuberia[2];
        if(pipe(tuberia)==-1){
                perror("pipe");
                return -1;
        }

        int pid = fork();

        switch(pid){
                case -1:
                        perror("fork");
                        return -1;
                        break;
                case 0:
                        printf("Hijo, lector de la tuberia (%i)\n", pid);
                        close(0);
                        dup2(tuberia[0], 0);
                        close(tuberia[0]);
                        close(tuberia[1]);
                        execlp(argv[3], argv[3], argv[4], 0);
                default:
                        printf("Padre, escritor de la tuberia (%i)\n",pid);
                        close(1);
                        dup2(tuberia[1],1);
                        close(tuberia[0]);
                        close(tuberia[1]);
                        execlp(argv[1],argv[1],argv[2],0);
        }
        return 0;
}
