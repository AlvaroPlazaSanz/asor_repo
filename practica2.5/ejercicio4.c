#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
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


        while(1){

                fd_set rfd;
                struct timeval tv;
                int ret;
                char buffer[80];


                FD_ZERO(&rfd);
                FD_SET(0, &rfd);
                FD_SET(sd, &rfd);

                tv.tv_sec = 2;
                tv.tv_usec = 0;

                if((ret = select(sd+1, &rfd, NULL, NULL, &tv)) == -1){
                        perror("Error al hacer el select.\n");
                        return -1;
                }


                if(FD_ISSET(0, &rfd)){

                        int n = read(0, &buffer, sizeof(buffer));
                        if(n == -1){
                                perror("Error al hacer la lectura.\n");
                                return -1;
                        }

                        buffer[n] = '\0';

                        if(strcmp(buffer, "t\n") == 0){
                                struct tm *lt;
                                time_t t;
                                time(&t);
                                lt = localtime(&t);

                                if(lt == NULL){
                                        perror("Error en localtime.\n");
                                        return -1;
                                }

                                char cad[100];

                                strftime(cad, 100, "%H:%M:%S\n", lt);
                                printf("t de stdin: %s\n", cad);
                        }
                        else if(strcmp(buffer, "d\n") == 0){

                                struct tm *lt;
                                time_t t;
                                time(&t);
                                lt = localtime(&t);

                                if(lt == NULL){
                                        perror("Error al hacer el localtime\n");
                                        return -1;
                                }
                                char cad[100];

                                strftime(cad, 100, "%d/%m/%y\n", lt);
                                printf("d de stdin: %s\n", cad);


                        }
                        else if(strcmp(buffer,"q\n") == 0){
                                printf("q de stdin: Saliendo...\n");
                                close(sd);
                                return 0;

                        }
                        else{
                                buffer[n-1]='\0';
                                printf("Comando %s leido de stdin no soportado.\n", buffer);
                        }

                }
                else if(FD_ISSET(sd, &rfd)){
                        struct sockaddr_storage add;
                        socklen_t addrlen = sizeof(struct sockaddr_storage);

                        int n = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &add, &addrlen);

                        if(n == -1){
                                perror("Error al hacer el recvfrom\n");
                                return -1;
                        }

                        buffer[n] = '\0';

                        char host[NI_MAXHOST], serv[NI_MAXSERV];

                        if((rc = getnameinfo((struct sockaddr *) &add, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST) == -1)){
                                perror("Error al hacer el getnameinfo\n");
                                return -1;
                        }

                        printf("%d bytes de %s:%s\n", n, host, serv);

                        if(strcmp(buffer, "t\n") == 0){
                                struct tm *lt;
                                time_t t;
                                time(&t);
                                lt = localtime(&t);

                                if(lt == NULL){
                                        perror("Error en localtime.\n");
                                        return -1;
                                }

                                char cad[100];
                                strftime(cad, 100, "%H:%M:%S\n", lt);
                                sendto(sd, cad, strlen(cad)+1, 0, (struct sockaddr *) &add, addrlen);
                        }
                        else if(strcmp(buffer, "d\n") == 0){
                                struct tm *lt;
                                time_t t;
                                time(&t);
                                lt = localtime(&t);

                                if(lt == NULL){
                                        perror("Error al hacer el localtime\n");
                                        return -1;
                                }

                                char cad[100];

                                strftime(cad, 100, "%d/%m/%y\n", lt);
                                sendto(sd, cad, strlen(cad)+1, 0, (struct sockaddr *) &add, addrlen);
                        }
                        else if(strcmp(buffer,"q\n") == 0){
                                printf("Saliendo...\n");
                                close(sd);
                                return 0;
                        }
                        else{
                                buffer[n-1]='\0';
                                printf("Comando %s no soportado.\n", buffer);
                        }
                }
        }
        return 0;
}
