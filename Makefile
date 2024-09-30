<<<<<<< HEAD
obj-m += stack.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
=======
obj-m += stackk.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

>>>>>>> origin/stack
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
