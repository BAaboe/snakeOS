CC := ~/opt/cross/bin/i686-elf-gcc
CCFLAGS := -ffreestanding -nostdlib -nostartfiles -fno-stack-protector -I include/ -m32 -T kernel/kernel.ld

CFILES := kernel/main.c kernel/drivers/vga.c kernel/printing.c

all: bootloader
	nasm -f bin bootloader/mbr.asm -o build/bootloader.o

	nasm -f elf32 kernel/kernel_entry.asm -o build/kernel_entry.o
	$(CC) $(CCFLAGS) build/kernel_entry.o $(CFILES) -o build/kernel.bin

	
	dd if=/dev/zero of=build/bilde.img bs=512 count=20
	dd if=build/bootloader.o of=build/bilde.img bs=512 seek=0
	dd if=build/kernel.bin of=build/bilde.img bs=512 seek=1

run: all
	qemu-system-x86_64 -drive file=build/bilde.img,format=raw

clean:
	rm -rf build/*
