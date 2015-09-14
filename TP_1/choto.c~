#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main (int argc, char *argv[]) {
        pid_t hijo1, hijo2;
        );
        hijo2 = fork();
        if((hijo1 = fork()) == 0){
            execlp ("kcalc", "kcalc", NULL);
            printf ("Ap. 1 ejecutada\n");
        }
        if (hijo2 == 0){
            execlp ("xload", "xload", NULL);
            printf ("Ap. 2 ejecutada\n");
        }
        return 0;
}
