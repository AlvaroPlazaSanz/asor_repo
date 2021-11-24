#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>


// ¿Qué sucede si el proceso padre termina antes que el hijo (observar el PPID del proceso hijo)?
// Sucede que se termina la ejecución pero posteriormente se ejecuta el hijo
//  ¿Y si el proceso que termina antes es el hijo (observar el estado del proceso hijo con ps)?
//  Si termina antes el hijo, el padre espera a que termine el hijo su ejecución.


void mostrar(pid_t pid){

        pid_t pgid = getpgid(pid);
        pid_t sid = getsid(pid);

        if(pid == 0){
                if(chdir("/tmp")==-1) perror(" CWD error");
                else sid = setsid();
                                                                                }

                printf("PID:%i\n", getpid());
                printf("PPID:%i\n", getppid());
                printf("PGID:%i \n", pgid);
                printf("SID:%i\n", sid);

                struct rlimit lim;
                if(getrlimit(RLIMIT_NOFILE, &lim)==1) perror("Limit error");
                else printf("Maximo ficheros:%ld\n", lim.rlim_max);


                char buff[4096];
                if(getcwd(buff, sizeof(buff))==NULL) perror("CWD error");
                else printf("CWD:%s\n", buff);                                                                       

}



int main(int argc, char **argv){

        pid_t pid = fork();

        switch(pid){
                case -1:
                        perror("Error en el fork");
                        return 1;

                case 0:
                        //sleep(10);
                        printf("Proceso Hijo\n");
                        mostrar(pid);
                        break;
                case 1:
                        sleep(5);
                        printf("Proceso Padre\n");
                        mostrar(pid);
                        break;
        }

        return 0;
  
}
