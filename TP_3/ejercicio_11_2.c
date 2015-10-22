/*
 * ejercicio_11.c
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

/*11) Realice un programa que imprima su PID, PPID, PGID y cree tres procesos hijos
 * que colaboran para realizar las siguientes tareas:
 * - El primer proceso hijo ejecuta la orden grep palabra fichero1. Escribiendo el
 * resultado de su ejecución en una tubería.
 * - El segundo proceso hijo ejecuta la orden grep palabra fichero2. Escribiendo el
 *   resultado de su ejecución en la misma tubería utilizada por el primer proceso
 *   hijo.
 * - El tercer proceso hijo utilizando la orden wc -l, tomará como entrada los datos
 *   almacenados en la tubería.
 * - Una vez que crea todos los procesos hijos, el proceso padre indicará el inicio de
 *   la ejecución de sus hijos enviándoles a cada uno una señal SIGUSR1.
 * 
 * Ejemplo de ejecución: ./programa palabra fichero1 fichero2
 * 
 * Consideraciones:
 * - No se permite la utilización de la llamada al sistema system().
 * - Validar la cantidad de parámetros enviados al programa, si no coinciden con lo
 *   solicitado mostrar un error y terminar.
 * 
 * */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wait.h>
int i;

void funcion(int sig){
	//~ if (sig == SIGUSR1){
		//~ raise(SIGCONT);
	//~ }
	printf("Buenas\n");
	return;
	//execlp("grep", "grep", argv[1], argv[i+2], NULL);
}

int main(int argc, char **argv)
{
	pid_t hijo[3];
	int pipa[2], estado;
	if (argc != 4){
		perror("USO: ./ejercicio_11_2 palabra fichero1 fichero2\n");
		exit(1);
	}
	
	if (pipe(pipa)==-1){
		perror("ERROR EN CREACION DE TUBERIA\n");
		exit(1);
	}
	printf("PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgid(getpid()));
	
	printf("tuberia creada\n");
	for (i = 0; i < 3; i++){
		if ((hijo[i]=fork()) == 0){
			printf("i=%d\n", i);
			if (i < 2){
				printf("hijo-%d creado, PID= %d, %s\n", i, getpid(), argv[i+2]);
				
				//raise(SIGSTOP);
				//printf("pipa[1]=%d\n", pipa[1]);
				if (signal(SIGUSR1, funcion)==SIG_ERR){
					perror("Error");
					exit(1);
				}
				if (pipa[1] != STDOUT_FILENO){
					if (dup2(pipa[1], STDOUT_FILENO) == -1){
						perror("Duplicado de desc.");
						exit(1);
					}
					close(pipa[1]);
					close(pipa[0]);
				}
				while(1)/*{
					printf("xax %d\n", getpid());
					pause();
				}*/
				printf("ejecuta\n");
				execlp("grep", "grep", argv[1], argv[i+2], NULL);
			}
			if (i==2){
				//tercer hijo hace algo.
				printf("hijo-%d creado, PID= %d\n", i, getpid());
				
				//printf("descriptores abieertooossssh\n");
				//raise(SIGSTOP);
				if (signal(SIGUSR1, funcion)==SIG_ERR){
					perror("Error");
					exit(1);
				}
				if (pipa[0] != STDIN_FILENO){
					if (dup2(pipa[0], STDIN_FILENO) == -1){
						perror("Duplicado de desc.");
						exit(1);
					}
					close(pipa[1]);
					close(pipa[0]);
				}

				while(1)/*{
					printf("sdsd %d\n", getpid());
					pause();
				}*/
				execlp("wc","wc","-l", NULL);
			}
		}
	}
	/*if ((hijo1 = fork()) == 0){
		printf("hijo1 creado\n");
		if(dup2(pipa[1], STDOUT_FILENO) == -1){
			perror("pipa");
			exit(1);
		}
		close(pipa[0]);
		execlp("grep", "grep", argv[1], argv[2], NULL);
	}
	if ((hijo2 = fork()) == 0){
		printf("hijo2 creado\n");
		if(dup2(pipa[1], STDOUT_FILENO) == -1){
			perror("pipa 2");
			exit(1);
		}
		execlp("grep", "grep", argv[1], argv[3], NULL);
	}
	if ((hijo3 = fork()) == 0){
		printf("hijo3 creado\n");
		if (dup2(pipa[0], STDIN_FILENO) == -1){
			perror("pipa");
			exit(1);
		}
		close(pipa[1]);
	}*/
	//~ for (i=0; i<3; i++)
		//~ wait(NULL);
	sleep(5);
	for (i = 0; i < 3; i++){
		printf("envio señal a: hijo-%d\n", i);
		if (kill(hijo[i], SIGUSR1) != 0){
			perror("error kill");
			exit(1);
		}
		//wait(&estado);
	}
	for (i=0; i<3; i++){
		if (wait(&estado) == hijo[i])
			printf("teminó hijo-%d\n", i);
	}
	return 0;
}

