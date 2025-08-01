CC := ~/opt/cross/bin/i686-elf-gcc
CCFLAGS := -ffreestanding -nostdlib -nostartfiles -fno-stack-protector -I include/ -m32 -T kernel/kernel.ld

CFILES := kernel/main.c kernel/drivers/vga.c kernel/printing.c kernel/error.c kernel/time.c kernel/keyboard.c kernel/util.c kernel/drivers/pc_speaker.c

all: bootloader
	nasm -f bin bootloader/mbr_fdd.asm -o build/bootloader.o

	nasm -f elf32 kernel/kernel_entry.asm -o build/kernel_entry.o
	$(CC) $(CCFLAGS) build/kernel_entry.o $(CFILES) -o build/kernel.bin

	
	dd if=/dev/zero of=build/bilde.img bs=512 count=2880
	dd if=build/bootloader.o of=build/bilde.img bs=512 seek=0 conv=notrunc
	dd if=build/kernel.bin of=build/bilde.img bs=512 seek=1 conv=notrunc

run: all
	qemu-system-x86_64 -drive file=build/bilde.img,if=floppy,format=raw -audiodev pa,id=speaker -machine pcspk-audiodev=speaker

clean:
	rm -rf build/*
