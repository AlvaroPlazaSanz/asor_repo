#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>


int main(){
  
  struct utsname buff; 
  if(uname(&buff)==-1){ 
    printf("Error %d: %s\n", errno,strerror(errno));
    return -1;
  }
  else{
    printf("sysname: %s\n", buff.sysname);                                                                               
    printf("nodename: %s\n", buff.nodename);                                                                             
    printf("release: %s\n", buff.release);                                                                               
    printf("machine: %s\n", buff.machine);                                                                               
    printf("version: %s\n", buff.version);                                                                               
    return 1; 
    
  }
  
}

