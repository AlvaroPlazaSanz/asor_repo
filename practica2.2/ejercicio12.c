#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>



int main(int argc, char **argv){

        int fd;

        if(argc != 2){
                perror("Uso incorrecto");
                return -1;
        }

        if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){

                perror("Error al abrir el archivo");
                return -1;
        }
        else{
                if(dup2(fd,1) == -1) {
                        perror("Error en el dup2");
                        return -1;
                }

        }

        printf("La salida se redirige.\n");

        close(fd);
        return 1;
}
