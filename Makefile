KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m := addsyscall.o

all: module user

module:
	make -C $(KDIR) M=$(PWD) modules

user:
	gcc -o test_addsyscall test_addsyscall.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f test_addsyscall
