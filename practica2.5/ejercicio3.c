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
        if(argc != 4){
                perror("Argumentos incorrectos.\n");
                return -1;
        }

        memset(&hints, 0, sizeof(hints));
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

        if((rc = connect(sd, res->ai_addr, res->ai_addrlen)) == -1){
                perror("Error al hacer el connect.\n");
                return -1;
        }


        char comm[2];
        comm[0] = argv[3][0];
        comm[1] = '\n';

        if((rc == sendto(sd, comm, 2, 0, res->ai_addr, res->ai_addrlen)) == -1){
                perror("Error al hacer el sendto().\n");
                return -1;
        }



        char buffer[100];
        struct sockaddr_storage add;

        socklen_t addr_len = sizeof(add);
        int n = recvfrom(sd, buffer, 100, 0, (struct sockaddr*) &add, &addr_len);
        buffer[n] = '\0';

        printf("%s", buffer);
        

        freeaddrinfo(res);


        return 0;
}
