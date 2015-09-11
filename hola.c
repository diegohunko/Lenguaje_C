#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main (int argc, char *argv[]){
	pid_t hijo;
	hijo = fork();
	if (hijo < 0){
		printf("Algo salio mal, un culo va a sangrar\n");
	}
	if (hijo == 0){
		printf("Soy el hijo de %d, mi identidad es %d\n", getppid(), getpid());
		//execlp("/bin/ps","ps",NULL);
	}
	else {
		wait(NULL);
		printf("Yo soy %d, mi hijo es %d\n", getpid(), hijo);
		//execlp("/bin/ls", "ls", "-l", NULL);
	}
	printf("Hola mundo\n");
	return 0;
}
