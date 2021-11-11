#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char **argv){


        struct stat buff;
        mode_t m;

        if(stat(argv[1], &buff) == -1){
                perror("Error. Uso: ./ej11 ruta");
                return -1;
        }
        else{

                m = buff.st_mode;
                char hard[strlen(argv[1]) + strlen(".hard")];
                char sym[strlen(argv[1]) + strlen(".sym")];
                strcat(strcpy(hard, argv[1]), ".hard");
                strcat(strcpy(sym, argv[1]), ".sym");


                if (S_ISREG(m)) {
                        if (link(argv[1], hard) == -1) {
                                perror("Error en la ejecucion del enlace rigido");
                                return -1;
                        }

                        if (symlink(argv[1], sym) == -1) {
                                perror("Error en la ejecucion del enlace simbolico");
                                return -1;
                        }
                }
                else{

                        perror("La ruta no es fichero regular");
                        return -1;
                }

        return 1;

        }


}
