#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main (int argc, char *argv[]) {
        pid_t hijo1, hijo2, fin1, fin2;
        int estado1, estado2;
        
        if((hijo1 = fork()) == 0){
            execlp ("ls", "ls", NULL);
            printf ("Ap. 1 ejecutada\n");
        }
        if ((hijo2 = fork()) == 0){
            execlp ("ps", "ps", NULL);
            printf ("Ap. 2 ejecutada\n");
        }
        fin1 = wait(&estado1);
        fin2 = wait(&estado2);
        printf("termino el proceso: %d, estado: %d\n", fin1, WEXITSTATUS(estado2));
        printf("termino el proceso: %d, estado: %d\n", fin2, WEXITSTATUS(estado2));
        return 0;
}
