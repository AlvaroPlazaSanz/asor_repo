#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <errno.h>


int main(int argc, char*argv[]){


        struct addrinfo info;
        struct addrinfo *res, *ac;
        char buff[256];

        memset(&info, 0, sizeof(struct addrinfo));
        info.ai_family = AF_UNSPEC;

        if(argc != 2){
                perror("Numero de argumentos incorrecto.\n");
                return -1;
        }

        if(getaddrinfo(argv[1], NULL, &info, &res) == 0){
                for(ac = res; ac != NULL; ac = ac->ai_next){
                        getnameinfo(ac->ai_addr, ac->ai_addrlen, buff, sizeof(buff), NULL, 0, NI_NUMERICHOST);
                        printf("%s %i %i\n", buff, ac->ai_family, ac->ai_socktype);
                }

        }
        else{
                perror("Error al hacer getaddrinfo(): Name or service not known.\n");
                return -1;
        }

        freeaddrinfo(res);
        return 0;

}
