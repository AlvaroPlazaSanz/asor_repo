
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>





int main(int argc, char **argv){

        int fd;

        if(argc != 2){
                perror("Uso incorrecto");
                return -1;
        }


        if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0645)) == -1){
                perror("Error al abrir el archivo");
                return -1;
        }

        int lock = lockf(fd, F_TEST,0);

        if(lock != -1){

                lockf(fd,F_TLOCK,0);
                printf("Hora actual: %ld\n", time(NULL));
                sleep(30);
                lockf(fd,F_ULOCK,0);

        }
        else{
                perror("Ya se encuentra bloqueado.\n");
                return -1;

        }

        close(fd);
        return 1;
}
