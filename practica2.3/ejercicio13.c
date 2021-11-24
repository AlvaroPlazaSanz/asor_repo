#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>



volatile int borrar = 1;


// kill -10 <pid>
void suspender(int s){
        borrar = 0;
}


int main(int argc, char **argv){

        if (argc != 2) {
                fprintf(stderr, "Usage: ./ej13 seconds\n");
                exit(EXIT_FAILURE);
         }


        struct sigaction sigus;
        long int s = strtol(argv[1], NULL, 10);
        char *rm = strdup("rm ");
        sigus.sa_handler = suspender;
        sigus.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &sigus, NULL);

        printf("pid:%i\n", getpid());


        sleep(s);
        if(borrar){
                strcat(rm,argv[0]);
                system(rm);
        }



        return 0;
}
