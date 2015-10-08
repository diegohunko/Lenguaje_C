# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

int main(){
	int fd[2], fd2[2];
	pid_t hijo, nieto;
	if (pipe(fd) != 0) {
		exit (1);
	}
	if ((hijo = fork())== 0){
		if ((nieto = fork()) == 0){
			dup2(fd2[1], 1);
			close(fd2[0]);
			execlp("more", "more", NULL);
		}else{
			dup2(fd[1], 1);
			dup2(fd2[0], 0);
			close(fd[0]);
			close(fd2[1]);
			execlp("grep", "grep", "-d", NULL);
			exit(1);
		}
	}else{
		dup2(fd[0], 0);
		close(fd[1]);
	}
	return 0;
}
