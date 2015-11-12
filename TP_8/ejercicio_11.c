/*
 * ejercicio_11.c
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
 * 
 * 11) Escriba un programa similar al comando grep de Unix que muestre todas las líneas
 * de un archivo que contengan una palabra determinada. Considere que las líneas de un
 * archivo pueden tener un tamaño variable
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	int fd;
	char linea;
	if ((argc != 3) || (strcmp(argv[1], "-h") == 0)){
		printf("USO:%s archivo palabra\n", argv[0]);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	while (read(fd, &linea, PATH_MAX) != -1){ //reconsiderable
		//if (strchr(&linea, ':'/*argv[2][0]*/)!=NULL){
			printf("%s\n", &linea);
		//}
	}
	close(fd);
	return 0;
}

