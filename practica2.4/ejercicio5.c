#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>



int main(){


        int tam, n, fd1, fd2, cs=0;
        fd_set set;

        char buff[256];

        if((fd1 = open("tub1", O_RDONLY | O_NONBLOCK)) == -1){
              perror("Error al abrir tuberia 1.\n");
              return -1;
        }

        if((fd2=open("tub2", O_RDONLY | O_NONBLOCK)) == -1){
                perror("Error al abrir tuberia 2.\n");
                close(fd2);
                return -1;

        }
  
        while(cs != -1){

                FD_ZERO(&set);

                FD_SET(fd1, &set);
                FD_SET(fd2, &set);

                if(fd1 > fd2) n = fd1 + 1;
                else n = fd2 + 1;
                cs = select(n, &set, NULL, NULL, NULL);

                if(cs == -1){
                        perror("Error al realizar el select.\n");
                        return -1;
                }
                else if(cs > 0){
                        if(FD_ISSET(fd1, &set)){
                                tam = read(fd1, buff, sizeof(buff)+1);
                                buff[tam] = '\0';

                                printf("Tub1: %s", buff);
                                close(fd1);

                                fd1 = open("tub1", O_RDONLY | O_NONBLOCK);
                        }
                        if(FD_ISSET(fd2, &set)){
                                tam = read(fd2, buff, sizeof(buff)-1);
                                buff[tam] = '\0';
                          
                                printf("Tub2: %s", buff);
                                close(fd2);

                                fd2 = open("tub2", O_RDONLY | O_NONBLOCK);
                        }
                }
        }

        close(fd1);
        close(fd2);

        return 0;
}

  
        
