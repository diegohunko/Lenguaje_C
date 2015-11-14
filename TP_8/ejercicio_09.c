/*
 * ejercicio_09.c
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

/*9) Escriba un programa que imprima el directorio de trabajo y lo recorra. Durante el
 * recorrido debe realizar las siguientes acciones:
 *  - Guardar el nombre de cada directorio encontrado en un archivo denominado
 *    directorios.log, dicho archivo debe crearse en cada ejecución del programa.
 *  - Borrar cada archivo regular que se encuentra.
 *  - Imprimir por pantalla el nombre de cada archivo de tipo FIFO y su tamaño.
 */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	char camino[PATH_MAX];
	DIR * dirp;
	struct dirent * infodir;
	struct stat statbuf;
	int fd;
	mode_t permisos;
	if (getcwd(camino, PATH_MAX) == NULL){
		printf("Directorio de trabajo: %s\n", camino);
		perror("No se pudo obtener el directorio de trabajo\n");
		exit(1);
	}
	printf("Directorio de trabajo: %s\n", camino);
	//se abre el directorio
	if ((dirp = opendir(camino)) == NULL){
		perror("No se pudo abrir el directorio\n");
		exit(1);
	}
	permisos = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	// creamos el archivo directorios.log
	if ((fd = open("directorio.log", O_CREAT | O_RDWR | O_TRUNC, permisos)) == -1){
		perror("open");
		exit(1);
	}
	//recorrer el directorio
	while ((infodir = readdir(dirp)) != NULL){
		stat(infodir->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)){
			if (write(fd, infodir->d_name, sizeof(infodir->d_name)) == -1){
				perror("No se pudo obtener el directorio de trabajo\n");
				//cerrar todo y salir
				exit(1);
			}
			//printf("%s Es un directorio\n", infodir->d_name);
		}else if (S_ISFIFO(statbuf.st_mode)){
			printf("Nombre: %s,\t Tamanio: %d\n", infodir->d_name, (int)statbuf.st_size);
		}else if (S_ISREG(statbuf.st_mode)){
			//borrar archivo
			printf("%s es un Archivo regular y sera borrado\n", infodir->d_name);
			remove(infodir->d_name);
		}
	}
	closedir(dirp);
	close(fd);
	return 0;
}

