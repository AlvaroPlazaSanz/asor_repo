#include <stdio.h>
#include <unistd.h>
#include <errno.h>



int main(){


        int ex = setuid(0);
        if(ex == -1) perror("Error en setuid(0)");
        return 1;


}
