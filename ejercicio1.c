#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(void){
	int a, b, c;
	pid_t hijo;
	a=1;
	b=3;
	c=a+b;
	hijo = fork();
	if (hijo == 0){
		printf("soy el hijo de %d\n", getppid());
	}
	else{
		printf("soy el padre de %d\n", hijo);
		Printf("Pendejos malcriados\n");
	}
	//printf("Hola mundo! soy %d\n", hijo);
	return 0;
}
