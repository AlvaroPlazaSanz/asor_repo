#include <stdio.h>                                                                                                   
#include <errno.h>                                                                                                   
#include <unistd.h>                                                                                                  
#include <unistd.h>                                                                                                  
#include <string.h>
#include <sys/utsname.h>                                                                                             
#include <sys/types.h>



int main(){
  
printf("Longitud máxima Args: %li\n", sysconf(_SC_ARG_MAX));                                                          
printf("Máximo hijos: %li\n", sysconf(_SC_CHILD_MAX));                                                                
printf("Máximo ficheros: %li\n", sysconf(_SC_OPEN_MAX));                                                              
return 1; 
  
}
