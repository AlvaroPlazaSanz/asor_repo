#include <sys/utsname.h>                                                                                             
#include <sys/types.h>                                                                                              
#include <unistd.h>                                                                                                 
#include <string.h>                                                                                                  
#include <stdio.h>                                                                                                  
#include <stdlib.h>                                                                                                 
#include <errno.h>


int main(){
  
  printf("UID Real: %d\n", getuid());                                                                                  
  printf("UID Efectivo: %d\n", geteuid());                                                                             
  return 1; 
  
  
}

// Para poder asegurar que el bit setuid está activado en el fichero deberíamos comprobar que el uid real
// es diferente del uid efectivo, lo que significaría que le hemos otorgado permisos a otro usuario.
