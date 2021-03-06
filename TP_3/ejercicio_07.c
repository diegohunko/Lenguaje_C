/*
 * ejercicio_07.c
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

/*7) Escriba un programa que cree un proceso hijo. Cada uno de los procesos debe
 * imprimir alternadamente una línea en la salida estándar, el proceso padre debe imprimir
 * en las líneas impares y el proceso hijo en las líneas pares (hasta el valor veinte):
 * Padre: 1
 * Hijo: 2
 * Padre: 3
 * Hijo: 4
 * Los procesos deben sincronizarse mediante el envío de la señal SIGUSR1.
 * 
 * */
//ejercicio_07.c en pastebin: http://pastebin.com/cmj20tDA
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
void manejame_esta_papa(int sig);

int i=1, contador=2;

int main(int argc, char **argv)
{
	pid_t hijo;
	if ((hijo = fork()) == 0){
		//do something kid
		//printf("veo si manejo la señal\n");
		if (signal(SIGUSR1, manejame_esta_papa) == SIG_ERR){
			perror("Error en el manejo de la señal :'(");
			exit(1);
		}
		while (1){
			
			if ((contador%2) == 0){
				pause();
				printf("Hijo: \t %d, \t PID= \t %d\n", contador, getpid());
				kill(getppid(), SIGUSR1);
			}
			
			if(contador==20)
				exit(0);
			contador++;
		}
	}else{
	//do something dad
		if (signal(SIGUSR1, manejame_esta_papa)== SIG_ERR){
			perror("Papá no sabe manejar una señal :(");
			exit(1);
		}
		
		while (1){
			if ((i%2) != 0){
				printf("Padre: \t %d, \t PID= \t %d\n", i, getpid());
				kill(hijo, SIGUSR1);
				pause();
			}
			if(i==20)
				exit(0);
			i++;
		}
	}
	wait(NULL);
	printf("llego al final\n");
	return 0;
}//fin main

void manejame_esta_papa(sig){
	if (sig == SIGUSR1){
	}
	return;
}
