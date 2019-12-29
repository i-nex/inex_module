EXTRA_CFLAGS += -O2
obj-m += inex.o
CC = gcc
KVER := $(shell uname -r)
KSRC := /lib/modules/$(KVER)/build

all: 
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD) modules

install:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD) modules
	sudo insmod inex.ko

clean:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD) clean
	
remove: 
	sudo rmmod inex
	make -C /lib/modules/$(KVER)/build M=$(PWD) clean
	
