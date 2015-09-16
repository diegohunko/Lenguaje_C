/*
 * ejercicio09.c
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
/*9) Desarrolle un programa que reciba dos parámetros a través de la línea de comandos,
 * el primero debe indicar el tipo de operación y el segundo debe ser un valor entero (N)
 * que indica la cantidad de procesos a crear.
 * El tipo de operación indica la forma de crear los procesos: si es “a” el programa debe
 * crear un hijo, el cual a su vez creará otro, y así sucesivamente, de modo que cada uno
 * desciende del anteriormente creado, hasta llegar a crear N procesos; si es “b” el
 * programa debe crear los N procesos, todos con un padre en común.
 * Cada hijo debe mostrar su SID, PGID, PPID, PID y terminar.
 * Se debe validar la cantidad de parámetros enviados al programa, si no coinciden con lo
 * solicitado se debe mostrar un mensaje de error y terminar.
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i, estado, numerodehijos;
	if (argc == 3){
		numerodehijos = atoi(argv[2]);
		if (numerodehijos <= 0){
			printf("El segundo parametro debe ser mayor que cero\n.");
		}
		else{
			pid_t hijos[numerodehijos];
			if (strcmp(argv[1], "a") == 0){
				i = 0;
				do{
					hijos[i] = fork();
					if (hijos[i] == 0)
					{
						printf("Mi PID= %d, mi PPID= %d, mi PGID= %d, mi SID= %d\n", getpid(), getppid(), getpgid(hijos[i]), getsid(hijos[i]));
					}else{
						wait(&estado);
						exit(0);
					}
					i++;
				}while (i < numerodehijos);
			}
			else if (strcmp(argv[1], "b") == 0){
				for (i = 0; i < numerodehijos; i++)
				{
					hijos[i] = fork();
					if (hijos[i] == 0)
					{
						printf("Mi PID= %d, mi PPID= %d, mi PGID= %d, miSID= %d\n", getpid(), getppid(), getpgid(hijos[i]), getsid(hijos[i]));
						exit(0);
					}else{
						wait(&estado);
					}
				}
				/*si es “b” el programa debe crear la cantidad
				* indica de hijos, todos con un padre en común.*/
			}
			else{
				printf("debe ser \"a\" o \"b\", sin comillas\n.");
			}
		}
	}
	else{
		printf("cantidad de parametros invalida.\n");
	}	
	return 0;
}

