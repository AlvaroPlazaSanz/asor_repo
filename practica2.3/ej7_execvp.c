#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char **argv){

        if(argc != 3){
                perror("Argumentos incorrectos\n");
                return 0;
        }

        execvp(argv[1], &argv[1]);

        printf("El comando terminó de ejecutarse\n");


        return 1;
}
