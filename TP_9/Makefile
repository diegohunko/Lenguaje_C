obj-m := ejercicio_01.o
obj-m := ejercicio_02.o
obj-m := ejercicio_03.o

KDIR :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
EXTRA_CFLAGS := -I/usr/realtime/include -I/usr/include/ -ffast-math -mhard-float
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f *.o *.ko *~ Module.symvers modules.order *.mod.c
