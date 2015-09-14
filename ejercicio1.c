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
		printf("soy el hijo de %d, %d\n", getppid(), hijo);
	}
	else{
		printf("soy el padre de %d\n", hijo);
		printf("Pendejos malcriados %d\n", c);
	}
	//printf("Hola mundo! soy %d\n", hijo);
	return 0;
}
