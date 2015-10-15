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
/*
 * 1) Desarrolle un programa que solicite al usuario 10 valores enteros. Por cada valor
 * ingresado se debe obtener la cantidad de números enteros positivos menores al valor
 * ingresado divisibles por 4. Al final el programa debe imprimir cada valor ingresado y la
 * cantidad de números divisibles por 4 existentes. El programa debe aprovechar los
 * tiempos de E/S para calcular lo solicitado, implemente el ejercicio mediante tuberías sin
 * nombre.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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
{
	int tubo[2], tubo2[2], j, numero, divisible, i;
    pid_t hijo;
    j=0;
    while (j < 10){
        printf("divisible= %d. Ingrese un numero entero: ", divisible);
		numero = cargarEntero();
		if (numero < 0){
			printf("Error\n");
			//exit(1);
		}else{
			pipe(tubo);
			pipe(tubo2);
			if((hijo = fork()) == 0){
				//printf("ENTRE EN HIJO, CIERRO DESCRIPTORES\n");
				divisible = 0;
				close(tubo[1]);
				close(tubo2[0]);
				//printf("LEO NUMERO\n");
				read(tubo[0], &numero, sizeof(numero));
				//printf("numero= %d\n", numero);
				for (i = numero; i >= 4; i--){
					if ((i % 4 == 0)){
					//}else{
						divisible += 1;
						//printf("i= %d, divisible= %d\n", i, divisible);
						
					}
					//printf("i= %d, divisible= %d\n", i, divisible);
					//numero--;
				}
				//printf("i= %d, numero= %d, divisible= %d\n", i, numero, divisible);
				write(tubo2[1], &divisible, sizeof(divisible));
				exit(0);
			}else{
				//wait(&estado);
				//printf("ENTRE EN PADRE, CIERRO DESC.\n");
				close(tubo[0]);
				close(tubo2[1]);
				write(tubo[1], &numero, sizeof(numero));
				//wait(&estado);
				//printf("divisible= %d\n",divisible);
				read(tubo2[0], &divisible, sizeof(divisible));
				printf("Hay %d numeros divisible entre 4 y %d, j= %d\n", divisible, numero, j);
			}
		}
		j++;
    }
	
	return 0;
}

