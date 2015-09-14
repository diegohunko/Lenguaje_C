#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main (int argc, char *argv[]) {
       pid_t pid = fork();
        if(pid == 0){
            execlp ("kcalc", "kcalc", NULL);
            printf ("Ap. 1 ejecutada\n");
        }else{
            execlp ("xload", "xload", NULL);
            printf ("Ap. 2 ejecutada\n");
        }
        return 0;
}
