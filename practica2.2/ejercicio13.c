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
                dup2(fd,1);
                dup2(fd,2);
                printf("Salida estandar redirigida al fichero.\n");
                perror("Error redirigido al fichero.\n");


        }

        printf("La salida se redirige.\n");

        close(fd);
        return 1;
}




//¿Hay diferencia si las redirecciones se hacen en diferente orden?
// Si, el orden de las redirecciones es importante e influye en la ejecución.
//
//¿Por qué ls > dirlist 2>&1 es diferente a ls 2>&1 > dirlist?
// Son diferentes porque en el primer caso la salida se envia al fichero y luego se redirige la salida de error
// al fichero mientras que en el segundo caso la salida de error estandar se redirige a la saida estandar y luego
// esa salida al fichero por tanto en el segundo caso error no apunta directamente al fichero
//
//
