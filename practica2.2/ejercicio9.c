#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


//  El número major y minor asociado al dispositivo.
//  Numero inodo
//  Tipo fichero
//  Hora accedió última vez
//  ¿Qué diferencia hay entre st_mtime y st_ctime?:
//  - St_mtime contiene la ultima fecha de modificacion del contenido del fichero mientras que
//  st_ctime contiene la ultima fecha de modificacion del inodo (cambio de estado del fichero)

int main(int argc, char ** argv){


        struct stat buf;
        char *tipo;


        if(stat(argv[1], &buf) == -1){

                perror("Error en la ejecucion de stat");
                return -1;
        }


        if(argc == 2){

                printf("Major: %u\n", major(buf.st_dev));
                printf("Minor: %u\n", minor(buf.st_dev));
                printf("Inodo: %ld\n", buf.st_ino);

                if(S_ISREG(buf.st_mode)) tipo = "Tipo Regular";
                else if(S_ISDIR(buf.st_mode)) tipo = "Tipo Directorio";
                else if(S_ISLNK(buf.st_mode)) tipo = "Tipo enlace simbolico";
                printf("Tipo: %s\n", tipo);

                printf("Ultimo acceso: %s\n", ctime(&buf.st_atime));

        }

        return 1;
}
