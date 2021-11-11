#include <sys/types.h>                                                              
#include <sys/stat.h>                                                               
#include <unistd.h>                                                                 
#include <fcntl.h>    

int main(void){       
  
  mode_t msc;                                                                         
  msc = umask(0027);      
  
  int fd = open("ejer7", O_WRONLY | O_CREAT | O_TRUNC, 0645);                         
  if(fd==-1){                                                                         
    perror("Error al hacer el open");                                                   
    return fd;     
  }                                                                                   
  
  close(fd);                                                                          
  umask(msc);                                                                         
  return 0;      
  
}                                                                                     
