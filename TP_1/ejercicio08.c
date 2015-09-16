/*
 * ejercicio08.c
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
 
 /*
  * 
  * 8) Desarrolle un programa que imprima su PID, cree un nuevo grupo de procesos y dos
  * procesos hijos. El primer hijo debe ejecutar el comando whoami. El segundo hijo debe
  * ejecutar el comando w. Los procesos hijos se deben ejecutar secuencialmente. El
  * proceso padre debe finalizar su ejecución una vez que sus procesos hijos terminan.
  * 
  */


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t hijo1, hijo2, finhijo[2];
	int i, estado;
	
	printf("Mi PID es: %d\n", getpid());
	if (setpgid(0, 0) == -1)
		printf("Hubo un error en crear el grupo\n");
	else{
		if ((hijo1=fork()) == 0){
			execlp("whoami", "whoami", NULL);
		}
		if ((hijo2 = fork()) == 0){
			execlp("w", "w", NULL);
		}
	}
	for(i=0; i<2; i++){
		finhijo[i] = wait(&estado);
	}
	return 0;
}

