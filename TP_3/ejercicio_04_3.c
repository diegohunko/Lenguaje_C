/*
 * ejercicio_04_3.c
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
 * 
 * Implementar
 * ls -l | grep ^d | more
 */


#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wait.h>

int main(int argc, char **argv)
{
	int fd1[2], fd2[2];
	pid_t hijo1, hijo2, hijo3;
	if (pipe(fd1)==-1)
		exit(1);
	if (pipe(fd2)==-1)
		exit(1);
	
	if ((hijo1=fork())==0){ //ejecuta ls -l
		//se cierra estremo de lectura en fd1
		if (close(fd1[0]))
			exit(1);
		//se duplica salida estandar
		if (fd1[1] != STDOUT_FILENO){
			if (dup2(fd1[1], STDOUT_FILENO)==-1)
				exit(1);
			
		}
		execlp("ls", "ls", "-l", NULL);
	}
	
	if ((hijo2=fork())==0){ //ejecuta grep ^d
		//se cierra extremo de escritura en fd1
		if (close(fd1[1])==-1)
			exit(1);
		//se duplica extremo de lectura fd1
		if(fd1[0] != STDIN_FILENO){
			if (dup2(fd1[0], STDIN_FILENO)==-1)
				exit(1);
		}
		//se cierra extremo de lectura de fd2
		if (close(fd2[0])==-1)
			exit(1);
		//se duplica extremo de escritura de fd2
		if (fd2[1] != STDOUT_FILENO){
			if (dup2(fd2[1], STDOUT_FILENO)==-1)
				exit(1);
		}
		
		execlp("grep", "grep", "^d", NULL);
	}
	
	if ((hijo3=fork())==0){ //ejecuta more
		//se cierra extremo de escritura de fd2
		if (close(fd2[1])==-1)
			exit(1);
		//se duplica extremo de lectura de fd2
		if (fd2[0]!= STDIN_FILENO){
			if (dup2(fd2[0], STDIN_FILENO)==-1)
				exit(1);
		}
		execlp("more", "more", (char *) NULL);
	}
	
	if (wait(NULL)==-1)
		exit(1);
	if (wait(NULL)==-1)
		exit(1);
	if (wait(NULL)==-1)
		exit(1);
	return 0;
}

