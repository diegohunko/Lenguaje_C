/*
 * ejercicio11.c
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
/*11) Realice un programa que genere 2 hijos, donde:
 * - El primero debe imprimir el PID, PPID, UID y EUID, esperar 10 segundos y
 *   terminar.
 * - El segundo debe ejecutar el comando ps.
 * El proceso padre debe esperar por sus dos hijos, indicando cual va terminando y luego
 * finalizar.
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	pid_t hijo1, hijo2, fin[2];
	int i, estado;
	if ((hijo1 = fork()) == 0){
		printf("Mi PID= %d, mi PPID= %d, mi UID= %d, mi EUID= %d\n", getpid(), getppid(), getuid(), geteuid());
		sleep(10);
		_exit(EXIT_SUCCESS);
	}
	if ((hijo2 = fork()) == 0){
		execlp("ps","ps",NULL);
	}
	for (i = 0; i < 2; i++){
		fin[i] = wait(&estado);
		printf("Termino: %d\n", fin[i]);
	}
	
	return 0;
}

