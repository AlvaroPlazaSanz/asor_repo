#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <errno.h>

int main(){

struct sched_param param;

int politica = sched_getscheduler(0);        //SCHED_OTHER, SCHED_FIFO, SCHED_RR
int error = sched_getparam(0, &param);        // struct sched_param

if(politica == -1){
        perror("Se ha producido un error en sched_getscheduler()");
}
else{
        switch(politica){
                case SCHED_OTHER:
                        printf("Poltica: SCHED_OTHER\n");
                        break;
                case SCHED_FIFO:
                        printf("Politica: SCHED_FIFO\n");
                        break;
                case SCHED_RR:
                        printf("Politica: SCHE_RR\n");
                        break;
                default:
                        break;
        }
        int min = sched_get_priority_min(politica);
        int max = sched_get_priority_max(politica);
        int prio = param.sched_priority;

        if(prio == -1 | max == -1 | min == -1){
                perror("Se produjo un error");
        }
        else{
                printf("Prioridad proceso actual: %i\n", prio);
                printf("Min: %i\n", min);
                printf("Max: %i\n", max);
        }
}
}
