obj-m += device_number.o
KERNEL_DIR=/lib/modules/$(shell uname -r)
all:
	make -C $(KERNEL_DIR)/build M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR)/build M=$(CWD) clean
