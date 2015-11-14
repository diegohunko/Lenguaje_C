/*
 * ejercicio_01.c
 *
 * 1) Escriba un módulo que cargue diez tareas que se ejecuten en modo no periódico,
 * cada una de las tareas debe ejecutar la siguiente función:
 * void print(long i) {
 *    rt_printk("Soy la tarea %d, i = %ld\n", rt_whoami(), i);
 * }
 * i es un valor único que se pasa a cada tarea. Donde la tarea1 recibe 1, la tarea2 recibe 2
 * y así sucesivamente.
 *
 */



#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <rtai.h>
#include <rtai_sched.h>

MODULE_LICENSE("GPL");

#define LIMITE 10

static RT_TASK tarea[LIMITE];
long i;
void imprimir (long i) {
	rt_printk("Soy la tarea %d, i = %ld\n", rt_whoami(), i);
	return;
}

int init_module(void) {
	int retval;
	rt_set_oneshot_mode();
	start_rt_timer(1);
	for (i = 0; i<LIMITE; i++){
	        retval = rt_task_init(&tarea[i], imprimir, i, 1024, 0, 0, 0);
	        if (retval == EINVAL) rt_printfk("Estructura de tarea señalada por la tarea ya está en uso");
	        if (retval == ENOMEM) rt_printfk("El tamaño de la pila no pudo ser asignada a la pila");
	        /* controlar valor devuelto ...*/
	}
	for (i = 0; i < LIMITE; i++){
	        retval = rt_task_resume(&tarea[i]);
	        if (retval == EINVAL) rt_printfk("Estructura de tarea señalada por la tarea ya está en uso");
	        if (retval == ENOMEM) rt_printfk("El tamanio de la pila no pudo ser asignada a la pila");
	}
	return 0;
}

void cleanup_module(void) {
	stop_rt_timer();
	for(i=0;i<LIMITE;i++){
	        rt_task_delete(&tarea[i]);
	}
	return;
}

