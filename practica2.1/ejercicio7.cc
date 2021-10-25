#include <stdio.h>                                                                                                   
#include <stdlib.h>                                                                                                  
#include <unistd.h>                                                                                                  
#include <errno.h>                                                                                                   
#include <string.h>                                                                                                  
#include <sys/utsname.h>                                                                                             
#include <sys/types.h>



int main(){
  
  printf("Numero máximo de enlaces: %li\n", pathconf("/tmp", _PC_LINK_MAX));                                           
  printf("Tamaño máximo de ruta: %li\n", pathconf("/tmp", _PC_PATH_MAX));                                              
  printf("Tamaño mácimo de nombre de fichero: %li\n", pathconf("/tmp", _PC_NAME_MAX));                                 
  return 1;
  
}
