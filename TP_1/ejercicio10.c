/*
 * ejercicio10.c
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
 * 10) Realice un programa que cree dos procesos hijos (hijo1 e hijo2), duerma 20
 * segundos y finalice. El hijo1 debe crear un hijo (hijo3), transformarse en líder de un
 * grupo de procesos, crear otro hijo (hijo4) y finalizar. Los procesos hijo2, hijo3 e hijo4
 * deben dormir 10 segundos y terminar.
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t hijo1, hijo2, hijo3, hijo4;
	if ((hijo1 = fork()) == 0){          //creacion de hijo1
		
		if ((hijo3 = fork()) > 0){       //creacion de hijo3
		
			setpgid(hijo1, getpgid());
			if ((hijo4 = fork()) > 0){   //creacion de hijo4
				exit(0);
			}else{
				sleep(10);               //hijo4 duerme 10''
			}
			
		}else{
			sleep(10);                   //hijo3 duerme 10''
		}
		
	}else{
		if((hijo2 = fork()) == 0){
			
		}
	}
	return 0;
}

