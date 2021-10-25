#include <stdlib.h>                                                                                                  
#include <stdio.h>                                                                                                  
#include <time.h>                                                                                                    
#include <errno.h>                                                                                                   
#include <sys/time.h>



int main(){
  
  time_t tim = time(NULL);                                                                                             
  struct tm *buff = localtime(&tim);                                                                                                                                                                                                        
  printf("Year: %i", buff->tm_year + 1900);  // Por defecto debemos sumarle 1900 al año 
  
  

  return 1;
}

