ifneq ($(KERNELRELEASE),)
obj-m		:= getcr3.o
else
KDIR		:= /lib/modules/$(shell uname -r)/build/
PWD		:= $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) V=1 modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean 

install:
	install -m 644 $(PWD)/*.ko /lib/modules/`uname -r`/kernel/drivers/misc
	if [ -d /etc/udev/rules.d -a ! -f /etc/udev/rules.d/99-getcr3.rules ] ; then \
		install -m 644 99-getcr3.rules /etc/udev/rules.d ; \
	fi
	depmod -a

autoload:
	if [ -d /etc/modules-load.d -a ! -f /etc/modules-load.d/getcr3.conf ] ; then \
		install -m 644 getcr3.conf /etc/modules-load.d ; \
	else \
		if [ -d /etc/sysconfig/modules -a ! -f /etc/sysconfig/modules/getcr3.modules ] ; then \
			install -m 755 getcr3.modules /etc/sysconfig/modules ; \
		fi \
	fi
endif
