#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
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


        for(int i = 0; i < NUM; i++){
                pid_t pid = fork();

                if(pid == -1){
                        perror("Error al hacer el fork().\n");
                        return -1;
                }
                if(pid == 0){
                        int rc = proceso(sd);
                        return rc;
                }
        }
        while(wait(NULL)>0);
        close(sd);
        return 0;
}




int proceso(int sd){

        int rc;

        while(1){

                char buffer[80];
                struct sockaddr_storage add;
                socklen_t addrlen = sizeof(struct sockaddr_storage);
                int n = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &add, &addrlen);

                if(n == -1){
                        perror("Error al hacer la lectura.\n");
                        return -1;
                }

                buffer[n] = '\0';
                char host[NI_MAXHOST], serv[NI_MAXSERV];
                if ((rc = getnameinfo((struct sockaddr *) &add, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST)) == -1){
                        perror("Error al hacer el getnameinfo().\n");
                        return -1;
                }
                printf("Server process PID: %d , %d bytes de %s:%s\n", getpid(), n, host, serv);


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
                        printf("Server process PID: %d ,  Saliendo...\n", getpid());
                        close(sd);
                        return 0;
                }
                else{
                        buffer[n-1]='\0';
                        printf("Comando %s no soportado.\n", buffer);
                }
        }
}

                  
                        
                       
                  
                    
      
