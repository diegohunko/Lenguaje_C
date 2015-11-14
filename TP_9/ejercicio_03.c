
/*3) Tres tareas (tarea1, tarea2 y tarea3) compiten para actualizar el valor de una variable
global llamada mivariable. El objetivo es alternar el valor de mivariable entre 0 y 2.
Consideraciones:
- El valor inicial de mivariable es 0.
- La tarea1 actualiza el valor de mivariable en 1 y señaliza a la tarea2.
- La tarea2 actualiza el valor de mivariable en 2 y señaliza a la tarea3.
- La tarea3 actualiza el valor de mivariable en 0 y señaliza a la tarea1.
Implemente la sincronización de las tareas mediante semáforos binarios. Cada tarea
debe realizar 10 iteraciones. El modo de ejecución es no periódico.
*/

#include <linux/kernel.h>    
#include <linux/module.h>    
#include <linux/version.h>    
#include <linux/errno.h>    
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_sem.h>

MODULE_LICENSE("GPL");

#define ITERACIONES 5
static SEM sem1, sem2, sem3;
static RT_TASK  tarea1;
static RT_TASK  tarea2;
static RT_TASK  tarea3;
int global = 0;

void funcion1(long arg) {
	int i;
	for (i=0; i < ITERACIONES; i++) {
		rt_sem_wait(&sem1);
		rt_printk("Aumentado: %d...!\n", global);
		global = 1;
		rt_printk("Valor: %d!\n", global);
		rt_sem_signal(&sem2);
	}
}

void funcion2(long arg) {
	int i;
	for (i=0; i < ITERACIONES; i++) {
		rt_sem_wait(&sem2);
		rt_printk("Disminuyendo: %d!...\n", global);
		global = 2;
		rt_printk("Valor: %d!\n", global);
		rt_sem_signal(&sem3);
	}
}

void funcion3(long arg) {
	int i;
	for (i=0; i < ITERACIONES; i++) {
		rt_sem_wait(&sem3);
		rt_printk("Disminuyendo: %d!...\n", global);
		global = 0;
		rt_printk("Valor: %d!\n", global);
		rt_sem_signal(&sem1);
	}
}
int init_module(void) {
	rt_set_oneshot_mode();
	start_rt_timer(1);

	rt_sem_init(&sem1, 1);
	rt_sem_init(&sem2, 0);
	rt_sem_init(&sem3, 0);
	rt_task_init(&tarea1, funcion1, 0, 1024, 1, 0, 0);
	rt_task_init(&tarea2, funcion2, 0, 1024, 1, 0, 0);
	rt_task_init(&tarea3, funcion3, 0, 1024, 1, 0, 0);
	rt_task_resume(&tarea1);
	rt_task_resume(&tarea2);
	rt_task_resume(&tarea3);
	return 0;
}

void cleanup_module(void) {
	rt_sem_delete(&sem1);
	rt_sem_delete(&sem2);
	return;
}
