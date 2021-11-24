#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define SLEEP_SECS  10

int main(int argc, char **argv){

        sigset_t blok;

        sigemptyset(&blok);
        sigaddset(&blok, SIGTSTP);
        sigaddset(&blok, SIGINT);
        sigprocmask(SIG_BLOCK, &blok, NULL);
        sleep(SLEEP_SECS);


        if(sigismember(&blok, SIGINT)==-1){
                printf("ERROR\n");
                return -1;
        }
        else if(sigismember(&blok, SIGINT)==0){
                printf("Señal INT no recogida\n");
                return 0;
        }
        if(sigismember(&blok, SIGTSTP)==-1){
                printf("ERROR\n");
                return -1;
        }
        else if(sigismember(&blok, SIGTSTP)==0){
                printf("Señal STP no recogida\n");                                                                                     return 0;
        }

        sigprocmask(SIG_UNBLOCK, &blok, NULL);
        printf("SEÑAL INT CAPTURADA:%i\n", SIGINT);
        printf("SEÑAL STP CAPTURADA:%i\n", SIGTSTP);


        return 1;


}
