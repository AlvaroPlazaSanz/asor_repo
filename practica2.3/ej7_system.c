#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){


        if(argc != 2){
                perror("Argumentos incorrectos\n");

        }

        system(argv[1]);
        printf("El comando terminó de ejecutarse\n");


        return 1;

}

// ¿En qué casos se imprime la cadena? ¿Por qué?
// La cadena se imprime cuando se llama a system ya que no sustituye la imagen del proceso por el del comando.
// Sin embargo cuando se llama execvp(), sustiye la imagen del proceso actual por el del comando.
