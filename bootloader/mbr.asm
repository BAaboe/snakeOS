[BITS 16]
ORG 0x7c00
jmp start

.data:
gdt_loaded_message: db "The gdt has been loaded.", 0

%include "bootloader/a20.asm"
%include "bootloader/printing.asm"
%include "bootloader/gdt.asm"

start:

cli
cld


mov ax, 0
mov es, ax

mov ah, 0x02 ; read sectors
mov al, 0x20 ; count
mov ch, 0 ; cylinder
mov dh, 0 ; head
mov cl, 2 ; sector
mov dl, 0x80 ; drive (First hard drive)
mov bx, 0x7e00
int 0x13

; Prints number of sectors loaded
mov ah, 0x0e
add al, '0'
int 0x10

; Set video mode
mov ah, 0x00
mov al, 0x13
int 0x10

; Load the GDT
mov ax, 0
mov ds, ax
call load_gdt

; Enable the a20 line
call enable_a20

; Enable protected mode
mov eax, cr0
or al, 1
mov cr0, eax


; Jump to 32bit
jmp 08h:0x00007e00


times 510-($-$$) db 0
db 0x55, 0xaa
