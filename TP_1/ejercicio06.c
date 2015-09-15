/*Realice un programa que cree 2 procesos hijos, donde:
- El primero debe imprimir su PID, PPID, SID y PGID, esperar 5 segundos y
terminar.
- El segundo debe imprimir su PID y luego ejecutar el comando ls -l.
El proceso padre después de crear los dos procesos hijos debe finalizar.
Responda:
- ¿Existen procesos zombies? Si la respuesta es afirmativa, indique cuáles.
- ¿Existen procesos huérfanos? Si la respuesta es afirmativa, indique cuáles.*/

#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t hijo1, hijo2;
    
    hijo1 = fork();
    if (hijo1 == 0){
        printf("Mi PID= %d, mi PPID= %d, mi PGID= %d, mi SID= %d, mi PGID= %d\n", getpid(), getppid(), getpgid(hijo1), getsid(hijo1), getpgid(0));
		sleep(5);
        exit(0);
    }
    
    hijo2 = fork();
    if (hijo2 == 0){
		printf("PID= %d\n", getpid());
        if (execlp("ls", "ls", "-l", NULL) < 0){
            exit(1);
        }
        
    }
    return 0;
}
