#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(int argc, char **argv){

// identificador de proceso, de proceso padre, de grupo de procesos y de sesión.
// Mostrar además el número máximo de ficheros que puede abrir el proceso y el directorio de trabajo actual.

        printf("PID:%i\n", getpid());
        printf("PPID:%i\n", getppid());
        printf("PGID:%i \n", getpgid(0));
        printf("SID:%i\n", getsid(getpid()));

        struct rlimit lim;

        if(getrlimit(RLIMIT_NOFILE, &lim)==1) perror("Limit error");
        else printf("Maximo ficheros:%ld\n", lim.rlim_max);

        char buff[4096];
        if(getcwd(buff, sizeof(buff))==NULL) perror("CWD error");
        else printf("CWD, DIR DE TRABAJO ACTUAL:%s\n", buff);


        return 1;

}
