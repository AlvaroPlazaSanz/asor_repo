#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


#define DAEMON_OUT "/tmp/daemon.out"
#define DAEMON_ERR "/tmp/daemon.err"
#define IN "/dev/null"


int main(int argc, char **argv){

        pid_t pid = fork();

        if(argc != 3){
                perror("Argumentos incorrectos\n");
                return 0;
        }

        if(pid == -1){
                perror("Error en el fork\n");
                return 0;

        }
        else if(pid == 0){
                setsid();
                chdir("/tmp");

                printf("Proceso hijo:\n");                                                                                           printf("ppid:%i\n pid:%i\n", getppid(), getpid());
                dup2(open(IN, O_RDONLY | O_CREAT | O_TRUNC, 0777), 0);
                dup2(open(DAEMON_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0777), 1);
                dup2(open(DAEMON_ERR, O_WRONLY | O_CREAT | O_TRUNC, 0777),2);

                execvp(argv[1], &argv[1]);


        }
        else{
                printf("Proceso padre:\n");
                printf("ppid:%i\n pid:%i\n", getppid(), getpid());
        }


        return 1;
}
