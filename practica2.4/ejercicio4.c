#include <iostream.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

//
//Abra la tubería con el nombre anterior en modo sólo escritura, y escriba en ella el primer argumento del programa. En otro terminal, leer de la tubería usando un comando adecuado.
//

int main(int argc, char **argv){


        if(argc < 2){
                perror("Argumentos incorrectos\n.");
                return -1;
        }

        int fd = open("tub", O_WRONLY);

        if(fd==-1){
                perror("Error al abrir la tuberia\n.");
                return -1;
        }

        write(fd,argv[1], strlen(argv[1])+1);
        close(fd);

        return 0;


}
