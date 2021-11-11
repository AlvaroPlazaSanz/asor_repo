#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


// El argumento que es la ruta a un directorio. El programa debe comprobar la corrección del argumento.
// Recorrerá las entradas del directorio de forma que:
//  -Si es un fichero normal, escribirá el nombre.
//  -Si es un directorio, escribirá el nombre seguido del carácter ‘/’.
//  -Si es un enlace simbólico, escribirá su nombre seguido de ‘->’ y el nombre del fichero enlazado. Usar readlink(2) y dimensionar adecuadamente el buffer.
//  -Si el fichero es ejecutable, escribirá el nombre seguido del carácter ‘*’.
//
//  Al final de la lista el programa escribirá el tamaño total que ocupan los ficheros (no directorios) en kilobytes.


int main(int argc, char **argv){


        if (argc == 2){

                DIR * directorio = opendir(argv[1]);
                struct dirent * contenido;
                int bSyze = 0;
                char path[PATH_MAX];
                int n;

                if(directorio == NULL){ // Directorio no valido
                        perror("Error al tratar de abrir el directorio");
                        return -1;
                }


                while((contenido = readdir(directorio)) != NULL){ // Vamos leyendo el directorio

                        //Siempre escribimos lo primero el nombre
                        printf("%s", contenido->d_name);


                        if(contenido->d_type == DT_REG){  // Es regular

                                printf("\n");
                                bSyze += contenido->d_reclen;
                        }
                        else if(contenido->d_type == DT_DIR){ //Es directorio
                                printf("/\n");
                        }
                        else if(contenido->d_type == DT_LNK){ //Es enlace Simbolico
                                if((n = readlink(contenido->d_name, path, PATH_MAX)) == -1){ //Error en symlink
                                        perror("Error al leer el symlink");
                                        return -1;
                                }
                                path[n] = '\0';
                                printf("->%s\n", path);
                        }

                }
                 printf("Tamaño: %d KBytes\n", bSyze);
                 closedir(directorio);
        }
        else{

                perror("Uso incorrecto");
                return -1;
        }




        return 1;


}
