all: kernel

kernel:
	$(MAKE) -C src/kernel

run:
	$(MAKE) -C src/kernel run

run-debugger:
	@qemu-system-i386 -s -S -m 48M -kernel build/kernel.elf

clean:
	$(MAKE) -C src/kernel clean

full: kernel run

iso: kernel
	cp build/kernel iso/kernel
	grub2-mkrescue -o build/bootable.iso iso

.PHONY: clean kernel run all