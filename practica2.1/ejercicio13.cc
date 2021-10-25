#include <stdio.h>                                                                                                   
#include <stdlib.h>                                                                                                  
#include <errno.h>                                                                                                   
#include <sys/time.h>                                                                                                
#include <time.h>     


int main(){        
  
  struct timeval intv1, intv2;   
  
  gettimeofday(&intv1, NULL);   
  int num = 0;        
  
  for(int i = 0; i < 1000000; ++i){       
    num += num;                                                                                                  
  }            
  gettimeofday(&intv2,NULL);   
  
  printf("Microsegundos empleados: %li\n", intv2.tv_usec-intv1.tv_usec);   
  return 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
}   
