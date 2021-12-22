#include <unistd.h>
#include <time.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    int main(int argc, char *argv[]){                                                                                                                                                                                                                                                         struct addrinfo hints;                                                                                                                   struct addrinfo *res;                                                                                                                                                                                                                                                             int sd, rc;                                                                                                                                                                                                                                                                       //Control argumentos
        if(argc != 3){                                                                                                                                   perror("Argumentos incorrectos.\n");                                                                                                     return -1;                                                                                                                       }                                                                                                                                                                                                                                                                                 memset(&hints, 0, sizeof(struct addrinfo));                                                                                                                                                                                                                                       hints.ai_family = AF_UNSPEC;                                                                                                             hints.ai_socktype = SOCK_DGRAM;                                                                                                                                                                                                                                                   //Control errores                                                                                                                        if((rc = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0){                                                                                     perror("Error al hacer el getaddrinfo().\n");                                                                                            return -1;                                                                                                                       }
                                                                                                                                                 if((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1){                                                                                    perror("Error al hacer el socket().\n");                                                                                                 return -1;                                                                                                                       }                                                                                                                                                                                                                                                                                 if(bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen) == -1){                                                                           perror("Error al hacer el bind().\n");                                                                                                   return -1;                                                                                                                       }                                                                                                                                
        freeaddrinfo(res);


        while(1){
                char buffer[8];
                int n;

                struct sockaddr_storage addr;                                                                                                            socklen_t addrlen = sizeof(struct sockaddr_storage);
                if((n = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &addr, &addrlen)) == -1){
                        perror(" Error al hacer el recvfrom().\n");
                        return -1;
                }
                buffer[n] = '\0';
                char host[NI_MAXHOST], serv[NI_MAXSERV];
                if((rc = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST)) == -1){
                        perror("Error al hacer el getnameinfo()\n");
                        return -1;
                }
           printf("%d bytes de %s:%s\n", n, host, serv);


                if(strcmp(buffer, "t\n") == 0){
                        struct tm *lt;
                        time_t tim;
                        time(&tim);
                        lt = localtime(&tim);

                        if(lt == NULL){
                                perror("Error en localtime()");
                                return -1;
                        }

                        char cadena[100];
                        strftime(cadena, 100, "%H:%M:%S\n", lt);
                        sendto(sd, cadena, strlen(cadena)+1, 0, (struct sockaddr*) &addr, addrlen);
                        }

                        else if(strcmp(buffer, "d\n") == 0){
                                struct tm *lt;
                                time_t tim;
                                time(&tim);
                                lt = localtime(&tim);

                                if(lt == NULL){
                                        perror("Error en localtime()\n");
                                        return -1;
                                }
                                char cadena[100];
                                strftime(cadena, 100, "%d/%m/%y\n", lt);
                                sendto(sd, cadena, strlen(cadena)+1, 0, (struct sockaddr *) &addr, addrlen);
                        }

                        else if(strcmp(buffer, "q\n") == 0){
                                printf("Saliendo...\n");
                                close(sd);
                                return 0;
                        }
                        else{
                                buffer[n-1]='\0';
                                printf("Comando %s no soportado.\n", buffer);
                        }
        }

        return 0;
}
