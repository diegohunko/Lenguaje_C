/*
 * ejercicio_12.c
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

/*12) Implemente un programa que cree un proceso hijo. El proceso hijo debe:
 * - ejecutar un bucle infinito en el que imprimen su PID una vez por segundo y
 * - manejar la señal SIGUSR1 (El manejador imprime el PPID del proceso).
 * El proceso padre debe realizar las siguientes acciones:
 * - esperar por tres segundos y suspender al proceso hijo,
 * - esperar por tres segundos y hacer continuar al proceso hijo,
 * - esperar cinco segundos y enviar una señal SIGUSR1 al proceso hijo y
 * - esperar diez segundos y enviar una señal SIGKILL al proceso hijo.
 * */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <signal.h>
void manejador(int sig);

int main(int argc, char **argv)
{
	pid_t hijo;
	if ((hijo=fork())==0){
		if (signal(SIGUSR1, manejador)==SIG_ERR){
			perror("changos");
			exit(1);
		}
		while (1){
			printf("Mi PID= %d\n", getpid());
			sleep(1);
		}
		pause();
	}
	printf("apolillo\n");
	sleep(3);
	printf("envio SIGSTOP\n");
	kill(hijo, SIGSTOP);
	printf("apolillo\n");
	sleep(3);
	printf("SIGCONT\n");
	kill(hijo, SIGCONT);
	printf("apolillo\n");
	sleep(5);
	printf("SIGUSR1\n");
	kill(hijo, SIGUSR1);
	printf("apolillo\n");
	sleep(10);
	printf("SIGKILL\n");
	kill(hijo, SIGKILL);
	return 0;
}

void manejador(sig){
	if (sig == SIGUSR1)
		printf("PPID= %d\n", getppid());
	exit(0);
}
