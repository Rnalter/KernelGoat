# Define the kernel directory and module name
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
MODULE_NAME := stackoverflow

# Set the default target
obj-m := $(MODULE_NAME).o

# Makefile rules
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean