#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                                                 


int main(int argc, char**argv){

        int tuberia_ph[2];
        int tuberia_hp[2];
        int fin = 0;
        char buffer[256];
        int n= 0;

        if(pipe(tuberia_ph)==-1){
                perror("pipe");
                return -1;
        }
        if(pipe(tuberia_hp)==-1){
                perror("pipe");
                return -1;
        }


        int pid = fork();

        switch(pid){
                case -1:
                        perror("fork");
                        return -1;
                        break;
                case 0:
                        close(tuberia_ph[1]);
                        close(tuberia_hp[0]);
                        while(!fin){
                                int rc = read(tuberia_ph[0], buffer,256);                                    
                                buffer[rc] = '\0';                                                                  
                                printf("Mensaje recibido: %s\n", buffer);
                                sleep(1);
                                if(++n == 10){
                                        write(tuberia_hp[1], "Q", 1);
                                        fin = 1;
                                }
                                else{
                                        write(tuberia_hp[1], "L", 1);
                                }
                        }
                        close(tuberia_ph[0]);
                        close(tuberia_hp[1]);
                        return 0;
                        break;
                default:
                        close(tuberia_ph[0]);
                        close(tuberia_hp[1]);
                        while(!fin){
                                printf("? ");
                                scanf("%s", buffer);
                                write(tuberia_ph[1], buffer, strlen(buffer)+1);
                                read(tuberia_hp[0], buffer, 1);
                                if(buffer[0]=='Q'){
                                        fin = 1;
                                }
                        }
                        close(tuberia_ph[1]);
                        close(tuberia_hp[0]);
                        return 0;
                        break;
                }
return 0;
}
