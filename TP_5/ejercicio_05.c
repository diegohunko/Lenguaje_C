/*
 * ejercicio_05.c
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

/* 5) Desarrolle un programa que solicite al usuario 10 valores enteros
 * mayores a 0. Por cada valor ingresado se debe obtener la cantidad de
 * números enteros positivos menores al valor ingresado divisibles por 4.
 * Al final se debe imprimir el valor cargado y la cantidad de números
 * divisibles por 4 existentes. El programa debe aprovechar los tiempos
 * de E/S para calcular lo solicitado, Implemente el ejercicio mediante
 * hilos que devuelven el resultado de cada cálculo.
 * 
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int divisible=0;

void *funcionDivisible(void *arg){
	int i, numero = (int)arg;
	for (i = numero; i >= 4; i--){
		if ((i % 4 == 0)){
			divisible += 1;
			//printf("i= %d, divisible= %d\n", i, divisible);
		}
		printf("i= %d, divisible= %d\n", i, divisible);
		//numero--;
	}
	pthread_exit(0);
}

int cargarEntero(void){
    int i;
    char valor[4];
    scanf("%3s", valor);
    while (getchar() != '\n');
    i = atoi(valor);
    if (i <= 0)
        i = -1;
    return i;
}

int main(int argc, char **argv)
{s
	pthread_t filo;
	int j = 0, un = 0;
	while (j<10){
		if ((un = cargarEntero()) == -1){
			perror("valor incorrecto");
			exit(-1);
			
		}
		pthread_create(&filo, NULL, funcionDivisible, &un);
		printf("Hay %d numeros divisible entre 4 y %d.\n", divisible, un);
		j++;
	}
	j=0;
	while (j<10){
		pthread_join(filo, NULL);
		j++;
	}
	return 0;
}

