/*
 * ejercicio_02.c
 *
 * 2) Escriba un módulo que cargue tres tareas que se ejecuten en modo periódico. La
 * tarea1 se debe ejecutar cada 1 segundo, la tarea2 cada 3 segundos y la tarea3 cada 5
 * segundos. Las prioridades son iguales. Cada tarea debe imprimir su número de tarea.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <rtai.h>
#include <rtai_sched.h>

MODULE_LICENSE("GPL");
static RT_TASK tarea1, tarea2, tarea3;

void funcion1(long arg) {
	while (1) {
		rt_printk("Nuevo Periodo....\n");    
		rt_task_wait_period();
	}
	return;
}

int init_module(void) {
	RTIME periodo_cant1, periodo_cant2, periodo_cant3;
	int retval;
        //cada tarea en su timer?
	rt_set_periodic_mode();
	periodo_cant1 = nano2count(1000000000);
	start_rt_timer(periodo_cant1);
	periodo_cant2 = nano2count(3000000000);
	start_rt_timer(periodo_cant2);
	periodo_cant3 = nano2count(5000000000);
	start_rt_timer(periodo_cant3);

	//tarea1
	retval = rt_task_init(&tarea1, funcion1, 0, 1024, 1, 0, 0);
	retval = rt_task_make_periodic(&tarea1, rt_get_time(), periodo_cant1);
	//tarea2
	retval = rt_task_init(&tarea2, funcion1, 0, 1024, 1, 0, 0);
	retval = rt_task_make_periodic(&tarea1, rt_get_time(), periodo_cant2);
	//tarea3
	retval = rt_task_init(&tarea3, funcion1, 0, 1024, 1, 0, 0);
	retval = rt_task_make_periodic(&tarea1, rt_get_time(), periodo_cant3);
	return 0;
}

void cleanup_module(void) {
	rt_task_delete(&tarea1);
	return;
}
