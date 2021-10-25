#include <stdio.h>                                                                                                   
#include <errno.h>                                                                                                   
#include <stdlib.h>                                                                                                  
#include <unistd.h>                                                                                                  
#include <time.h> 



int main(){
  
 time_t tim = time(NULL);                                                                                             
 printf("Hora en segundos desde Epoch: %li\n", tim); 
  
 return 1;
  
  
}
