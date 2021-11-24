#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int contadorSTP=0, contadorINT=0;

// señal INT = CTRL+C, señal STP = CTRL+Z                                                                                                                                                                                                                                                                                                                      void contador(int s){
        if(s == SIGTSTP) contadorSTP++;
        if(s == SIGINT) contadorINT++;

}


int main(int argc, char **argv){

        sigset_t blok;
        struct sigaction s;
        s.sa_handler = contador;

        sigaction(SIGINT,&s,NULL);
        sigaction(SIGTSTP,&s,NULL);

        sigemptyset(&blok);

        while(contadorINT + contadorSTP < 10){
                sigsuspend(&blok);
        }

        printf("Contador SEÑAL INT: %i\n", contadorINT);
        printf("Contador SEÑAL STP: %i\n", contadorSTP);


        return 1;


}

