/*
 * ejercicio_01.c
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

/*1) Realice un programa que permita la carga de una matriz de 5 x 5 de
 * enteros y genere 5 hilos que sumen las filas de la matriz
 * (Cada hilo realiza la suma de una fila y retorna el valor obtenido),
 * el hilo principal debe esperar por los otros hilos y mostrar el
 * resultado de la suma de todas las filas.
 * 
 */
#include <stdio.h>
#include <pthread.h>

int matriz[5][5];
struct argumento{
	int fila;
	int resultado;
};

void *sumar_fila(void *arg){
	struct argumento a = *(struct argumento *) arg;
	int j;
	a.resultado = 0;
	for(j = 0; j < 5; j++){
		a.resultado = a.resultado + matriz[a.fila][j];
		printf("%d\n", a.resultado);
	}
	pthread_exit(0);
}
int main(int argc, char **argv)
{
	int i, n;
	struct argumento dato;
	pthread_t hilos[5];
	for (i=0; i<5; i++){
		for (n=0; n<5; n++){
			printf("matriz[%d,%d]= ", i, n);
			scanf("%d",&matriz[i][n]);
		}
	}
	for (i=0; i<5; i++){
		dato.fila = i;
		pthread_create(&hilos[i], NULL, sumar_fila, (void *) &dato);
		printf("suma de la fila %d= %d\n",i , dato.resultado);
	}
	for (i=0; i<5; i++){
		pthread_join(hilos[i], NULL);
	}
	return 0;
}

