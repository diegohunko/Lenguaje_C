#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	int fd[2], fd2[2];
	pid_t hijo, nieto;
	if ((pipe(fd) != 0)&&(pipe(fd2) != 0)) {
		exit (1);
	}
	if ((hijo = fork())== 0){
		if ((nieto = fork()) == 0){
			printf("ENTRE EN NIETO\n");
			dup2(fd2[1], STDOUT_FILENO);
			//printf("fd2[0]= %d, STDIN_FILENO= %d", fd2[0], STDIN_FILENO);
			close(fd2[1]);
			execlp("more", "more", NULL);
		}else{
			printf("ENTRE EN HIJO\n");
			//printf("fd[0]= %d, STDIN_FILENO= %d", fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			//close(fd[0]);
			//printf("fd[0]= %d, STDIN_FILENO= %d", fd[0], STDIN_FILENO);
			//printf("fd[1]= %d, STDOUT_FILENO= %d", fd[1], STDOUT_FILENO);
			dup2(fd2[0], STDIN_FILENO);
			//printf("fd[1]= %d, STDOUT_FILENO= %d", fd[1], STDOUT_FILENO);
			close(fd2[1]);
			close(fd[0]);
			execlp("grep", "grep", "^d", NULL);
			exit(1);
		}
	}else{
		printf("ENTRE EN PADRE\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execlp("ls", "ls", "-l", NULL);
	}
	return 0;
}
