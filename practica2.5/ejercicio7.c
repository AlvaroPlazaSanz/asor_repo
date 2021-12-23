#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>


int main(int argc, char **argv){

        struct addrinfo hints;
        struct addrinfo *res;
        int rc, sd;

        //Control de argumentos
        if(argc != 3){
                perror("Argumentos incorrectos.\n");
                return -1;
        }

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;


        //Control de errores
        if((rc = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1){
                perror("Error al hacer el getaddrinfo().\n");
                return -1;
        }

        if((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1){
                perror("Error al hacer el socket().\n");
                return -1;
        }

        if((rc = bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) == -1){
                perror("Error al hacer el bind.\n");
                return -1;
        }


        freeaddrinfo(res);

        char buffer[80];
        memset(buffer, 0, sizeof(buffer));


        while(1){

                int n = read(0, buffer, sizeof(buffer));
                if(n == -1){
                        perror("Error de lectura\n");
                        return -1;
                }

                buffer[n] = '\0';

                if (strcmp(buffer, "Q\n") == 0) break;

                if((rc = send(sd, buffer, n, 0)) == -1){
                        perror("Error al hacer el send().\n");
                        return -1;
                }

                if((n = recv(sd, buffer, sizeof(buffer), 0)) == -1){
                        perror("Error al hacer el recv().\n");
                        return -1;
                }


                buffer[n] = '\0';
                printf("%s", buffer);

        }
        close(sd);
        return 0;
}
