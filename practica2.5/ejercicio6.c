#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>


#define NUM 4

int proceso(int sd);


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
        if((rc = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0){
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

        if((rc = listen(sd, 5)) == -1){
                perror("Error al hacer el listen.\n");
                return -1;
        }


        while(1){

                struct sockaddr_storage add;
                socklen_t addrlen = sizeof(add);
          
                int clsd = accept(sd, (struct sockaddr *) &add, &addrlen);
                if(clsd == -1){
                        perror("Error al hacer el accept.\n");
                        return -1;
                }

                char host[NI_MAXHOST], serv[NI_MAXSERV];
                if ((rc = getnameinfo((struct sockaddr *) &add, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV)) == -1){
                        perror("Error al hacer el getnameinfo().\n");
                        return -1;
                }

                printf("Conexion: %s:%s\n", host, serv);

                char buffer[80];

                int n = recv(clsd, buffer, sizeof(buffer), 0);
                if(n == -1){
                        perror("Error al hacer el recv.\n");
                        return -1;
                }

                while(n > 0){
                        buffer[n] = '\0';
                        int s = send(clsd, buffer, n, 0);

                        if(s == -1){ // Error de envio
                                perror("Error al hacer el send.\n");
                                return -1;
                        }

                        if((n = recv(clsd, buffer, sizeof(buffer), 0)) == -1){
                                perror("Error al hacer el recv.\n");
                                return -1;
                        }
                }
                printf("Conexion finished.\n");
                close(clsd);
        }
        return 0;
}
