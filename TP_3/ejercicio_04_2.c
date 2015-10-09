/*
 * ejercicio_04_2.c
 * 
 * Copyright 2015 Diego Fernandez <diego@diegonotbuc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wait.h>
//#include "tlpi_hdr.h"

int main(int argc, char **argv)
{
	int fd1[2], fd2[2]; /*estado2*/
	pid_t hijo, nieto;
	//printf("//creamos las tuberias\n");
	if (pipe(fd1) == -1){
		printf("pipe fd1\n");
	}
	//printf("%d, %d\n", fd1[0], fd1[1]);
	
	//printf("%d, %d\n", fd2[0], fd2[1]);
	//printf("//creamos hijo\n");
	if ((hijo = fork()) == 0){
		//printf("//creamos el nieto\n");
		if (pipe(fd2)==-1){
			printf("pipe fd2\n");
		}
		if ((nieto = fork())==0){
			//ejecutamos codigo del nieto
			//printf("//cerramos el extremo de lectura de fd2\n");
			if (close(fd2[0])==-1)
				printf("close fd2\n");
			
			//printf("//duplicamos el extremo de escritura de fd2\n");
			if (fd2[1] != STDOUT_FILENO){
				if (dup2(fd2[1], STDOUT_FILENO)==-1){
					printf("dup2 en nieto");
					exit(1);
				}
				//if (close(fd2[1])==-1){
				//	printf("close de fd2[0]");
				//	exit(1);
				//}
			}
			//printf("//ejecutamos ls -l\n");
			execlp("ls", "ls", "-l", NULL);
			
		}else{
			//ejecutamos codigo del hijo
			//printf("//cerramos extremo de escritura para fd2\n");
			if (close(fd2[1]) == -1){
				printf("close fd1\n");
				exit(1);
			}
			//printf("//duplicamos descriptor de lectura\n");
			if (fd2[0] != STDIN_FILENO){
				if (dup2(fd2[0], STDIN_FILENO) == -1)
					printf("dup2 en hijo\n");
				//if (close(fd1[0]) == -1)
				//	printf("close fd10\n");
			}
			//printf("//cerramos extremo de lectura para fd1\n");
			if (close(fd1[0]) == -1)
				printf("close fd2\n");
			//printf("//duplicamos descriptor de escritura para fd1\n");
			if (fd1[1]!=STDOUT_FILENO){
				if (dup2(fd1[1], STDOUT_FILENO)==-1)
					printf("dup2 para escritura\n");
				//if (close(fd2[1])==-1)
				//	printf("close fd2[1]\n");
			}
			
			//printf("//ejecucion de grep ^d\n");
			execlp("grep", "grep", "^d", NULL);
		}
		
	}else{
		//printf("//ejecutamos codigo del padre\n");
		//printf("//cerramos el extremo de escritura de fd1\n");
		if (close(fd1[1]) == -1)
			printf("close fd1[1]\n");
		
		//printf("//duplicamos entrada estandar para el padre, fd1\n");
		if (fd1[0] != STDIN_FILENO) {
			if (dup2(fd1[0], STDIN_FILENO) == -1)
				printf("dup2 padre\n");
			//if (close(fd1[1]) == -1)
			//	printf("close fd1[1]\n");
		}
		//wait(&estado2);
		//printf("//ejecutamos ls -l\n");
		execlp("more", "more", NULL);
		printf("Error en ls");
	}
		
	return 0;
}

