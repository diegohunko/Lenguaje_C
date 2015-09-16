/*
 * ejercicio07.c
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
 * 7) Escriba un programa que reciba una cantidad variable de nombres de archivo desde la
línea de comandos. Por cada nombre de archivo el programa debe crear un proceso hijo
que:
- Imprima su PGID, PPID, PID y el nombre del archivo; y
- Use una de las funciones de la familia exec() para ejecutar: wc -l
nombre_de_archivo.
Consideraciones:
- Los procesos hijos se deben ejecutar concurrentemente.
- El proceso padre debe indicar que proceso hijo va finalizando e indicando de
que manera finaliza (Normal o por una señal).
- Si no se pasa ningún nombre de archivo se debe mostrar un mensaje de error.*/

#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t hijo[argc], fin_hijo[argc];
	int i, estados;
	if (argc < 1){
		printf("Debe pasar al menos un nombre de archivo\n");
		exit(1);
	}
	else{
		for (i = 0; i < argc; i++){
			hijo[i] = fork();
			if (hijo[i]==0){
				printf("Mi PID= %d, mi PPID= %d, mi PGID= %d, Nombre archivo: %s\n", getpid(), getppid(), getpgid(hijo[i]), argv[i]);
				execlp("wc", "wc", "-l", argv[i], NULL);
			}
		}
		for (i = 0; i < argc; i++){
			fin_hijo[i] = wait(&estados);
			if (WIFEXITED (estados)){
				printf("el proceso: %d termino en forma normal\n", fin_hijo[i]);
			}
			if (WIFSIGNALED(estados)){
				printf("Hijo termino a causa de una señal\n");
			}
		}
	}
	return 0;
}

