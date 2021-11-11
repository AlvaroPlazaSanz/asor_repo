#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void){

        umask(0027);
        int fd = open("ejercicio7", O_WRONLY | O_CREAT | O_TRUNC, 0645);
        if(fd == -1) return fd;
        close(fd);
        return 0;
}                                                                                 
