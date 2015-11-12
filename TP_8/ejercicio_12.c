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

/*12) Desarrolle un programa que solicite al usuario un número n, luego permita la carga
 * de un vector de n elementos de tipo alumno y calcule la media aritmética de las notas de
 * los alumnos.
 * 	typedef struct {
 * 		char nombre[50];
 * 		int nota;
 * 	} alumno;
 * Consideraciones:
 * 	- Utilice asignación dinámica de memoria.
 * 	- Libere la memoria al final del programa.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
	char nombre[50];
	int nota;
} alumno;

int main(int argc, char **argv)
{
	int n;
	printf("Ingrese un numero: ");
	scanf("%d", n)
	
	return 0;
}

