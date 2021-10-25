#include <unistd.h>                                                            
#include <errno.h>                                                             
#include <stdio.h>                                                             
#include <string.h> 



int main(){
  
  for(int i = 1; i <= 255; ++i)
    printf("Información del error %i: %s\n", i, strerror(i)); 
  
  return 1;
  
}
