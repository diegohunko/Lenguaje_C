/*
 * hilos.c
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
 * 6) Dado el programa denominado hilos.c que ejecuta una serie de hilos
 * que se especifica por linea de comandos. Cada hilo obtiene la hora en
 * que comienza a correr y sigue corriendo hasta que pasan 5 segundos.
 * 
 */



#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/time.h>

void *horaInicio(void *arg){
	//imprimir hora de inicio de la hebra.
	struct tm *tiempop;
	time_t t;
	t = time(NULL);
	tiempop = localtime(&t);
	if (tiempop == NULL){
		perror("No se pudo obtener la hora");
		exit(1);
	}
	//tiempo = *tiempop;
	printf("Hora de inicio: %s\n", asctime(tiempop));//tp.tm_hour, tp.tm_min, tp.tm_sec, tp.tm_mday, tp.tm_mon, tp.tm_year + 1900);
	sleep(10);
	pthread_exit(0);
}
int main(int argc, char **argv)
{
	int limite, i;
	limite = atoi(argv[1]);
	pthread_t hilos[limite];
	if (argc != 2){
		perror("ERROR, USO: ./hilos N, donde N es el numero de hijos a crear.");
		exit(1);
	}
	for (i = 0; i < limite; i++){
		pthread_create(&hilos[i], NULL, horaInicio, NULL);
		printf("hilo-%d: %ld\n", i, hilos[i]);
	}
	for (i = 0; i<limite; i++){
		pthread_join(hilos[i], NULL);
	}
	return 0;
}

