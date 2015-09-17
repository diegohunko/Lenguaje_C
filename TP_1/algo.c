#include <sys/types.h> 
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>




int main (void){
        int i;
        pid_t pid1, pid2;
        for(i = 0; i < 2; i++){
                pid1 = fork();
                pid2 = fork();
                if (pid1 > 0)
                        printf("1\n");
                if (pid2 == 0)
                        printf("2\n");
        }
        exit(0);
}
