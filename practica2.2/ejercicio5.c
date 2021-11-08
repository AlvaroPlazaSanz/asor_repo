#include <sys/types.h>                                                              
#include <sys/stat.h>                                                               
#include <stdio.h>                                                                  
#include <unistd.h>                                                                 
#include <fcntl.h>  

int main(){                                                                                                                                                             
                                                                   
  int fd;                                                                                                                                                                                                                     
  fd = open("ejercicio5.txt", O_WRONLY | O_CREAT | O_TRUNC, 0645);  
  
  if(fd==-1){                                                                                 
    perror("Error al hacer el open");                                                   
    return fd;                                                                  
  }                                                                                                                                                                       
  close(fd);                                                                          
                                                                    
  return 0;                                                                           
}                                                                                                                              
