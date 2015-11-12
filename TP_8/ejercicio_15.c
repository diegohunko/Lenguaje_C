#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    char directorio[PATH_MAX];
    size_t tam = PATH_MAX;
    int yo, ello;
    if (argc == 3){
		if (strcmp(argv[1], "c") == 0){
			if (getcwd(directorio, tam)!= NULL){
				printf("%s\n", directorio);
			}
			yo = mkdir(argv[2], S_IRWXU | S_IRWXO);
			if (yo == 0){
				printf("directorio creado de forma correcta\n");
				printf("me voy al directorio recien creado::::>\n");
				ello = chdir(argv[2]);
				if (ello == 0){
					printf("Me he cambiado al nuevo directorio\n");
					if (getcwd(directorio, tam)!= NULL){
						printf("%s\n", directorio);
					}
				}else if (ello == -1){
					printf("Hubo un error.\n");
				}
			}
		}else if (strcmp(argv[1], "e") == 0){
			if (rmdir(argv[2]) == 0){
				printf("Eliminado.\n");
			}else{
				printf("Error\n");
				exit(1);
			}
		}else {
			printf("Error\n");
			exit(1);
		}
	}
    
    return 0;
}
