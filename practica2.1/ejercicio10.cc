#include <sys/utsname.h>                                                                                             
#include <sys/types.h>                                                                                              
#include <unistd.h>                                                                                                 
#include <string.h>                                                                                                  
#include <stdio.h>                                                                                                  
#include <stdlib.h>                                                                                                 
#include <errno.h>
#include <pwd.h>


int main(){
  
  printf("UID Real: %d\n", getuid());                                                                                  
  printf("UID Efectivo: %d\n", geteuid());  
  
  struct passwd *pas = getpwuid(getuid());    
  
  printf("Nombre de usuario: %s\n", pas->pw_name);                                                                     
  printf("Directorio HOME: %s\n", pas->pw_dir);                                                                        
  printf("Descripción de usuario: %s\n", pas->pw_gecos); 
  
  
  
  return 1; 
  
  
}
