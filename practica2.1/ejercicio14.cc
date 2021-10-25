#include <stdlib.h>                                                                                                  
#include <stdio.h>                                                                                                  
#include <time.h>                                                                                                    
#include <errno.h>                                                                                                   
#include <sys/time.h>



int main(){
  
  time_t tim = time(NULL);                                                                                             
  struct tm *buff = localtime(&tim);  
  
  char buffer[256];                                                                                                    
  strftime(buffer, 256, "%A, %B %d %Y, %H:%M", buff);  //Utilizamos el formato de strftime para mostrarlo como en el enunciado                                                                
  printf("%s\n", buffer);
  

  return 1;
}

