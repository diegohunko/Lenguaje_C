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
#include <wait.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc, char **argv)
{
	int i;
	if (argc != 4){
		perror("USO: ./ejercicio_11 palabra fichero1 fichero2\n");
		exit(1);
	}
	pid_t hijo1, hijo2, hijo3;
	int pipa[2];
	printf("PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgid(getpid()));
	if (pipe(pipa)==-1){
		perror("ERROR EN CREACION DE TUBERIA\n");
		exit(1);
	}
	printf("tuberia creada\n");
	if ((hijo1 = fork()) == 0){
		printf("hijo1 creado\n");
		if(dup2(pipa[1], STDOUT_FILENO) == -1){
			perror("pipa");
			exit(1);
		}
		close(pipa[0]); printf("CIERO\n");
		printf("ejecuto\n");
		execlp("grep", "grep", argv[1], argv[2], NULL);
	}
	if (pipe(pipa)==-1){
		perror("ERROR EN CREACION DE TUBERIA\n");
		exit(1);
	}
	if ((hijo2 = fork()) == 0){
		printf("hijo2 creado\n");
		if(dup2(pipa[1], STDOUT_FILENO) == -1){
			perror("pipa 2");
			exit(1);
		}
		close(pipa[0]); printf("CIERO\n");
		printf("ejecuto\n");
		execlp("grep", "grep", argv[1], argv[3], NULL);
	}
	if ((hijo3 = fork()) == 0){
		printf("hijo3 creado\n");
		if (dup2(pipa[0], STDIN_FILENO) == -1){
			perror("pipa");
			exit(1);
		}
		close(pipa[1]);
		execlp("wc","wc","-l",NULL);
	}
	for (i=0; i<3; i++)
		wait(NULL);
	return 0;
}

