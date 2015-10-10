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

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
void manejame_esta(int sig);

int main(int argc, char **argv)
{
	pid_t hijo; int i;
	if ((hijo = fork()) == 0){
		//do something kid
		signal(SIGUSR1, manejame_esta);
		kill(getppid(), SIGUSR1);		
	}else{
		//do something dad
		//pause();
		signal(SIGUSR1, manejame_esta);
		//printf("padre\n");
		kill(getppid(), SIGUSR1);
	}
	for(i=1;i<=20;i++){
		printf("%d\n",i);
	}
	scanf("%d", &i);
	return 0;
}

void manejame_esta(sig){
	printf("que haces\n");
}
