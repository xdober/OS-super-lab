ifneq ($(KERNELRELEASE),)
#kbuild syntax.
mymodule-objs :=mydev.o
obj-m :=mymodule.o
else
PWD :=$(shell pwd)
KVER :=$(shell uname -r)
KDIR :=/lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD)
clean:
	rm -f *.cmd *.o *.mod *.ko
endif
