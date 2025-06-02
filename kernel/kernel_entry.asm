[BITS 32]

[global kernel]
[extern kernel_main]

jmp kernel

%include "kernel/idt.asm"

section .text
init_pic:
; Pic 1
mov al, 0x11
out 0x20, al

mov al, 0x20
out 0x21, al

mov al, 4
out 0x21, al

mov al, 0x01
out 0x21, al

; Pic 2
mov al, 0x11
out 0xA0, al

mov al, 0x28
out 0xA1, al

mov al, 2
out 0xA1, al

mov al, 0x01
out 0xA1, al

mov al, 0b11111100
out 0x21, al
mov al, 0xff
out 0xA1, al

ret

kernel:
; Setting up the segments
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
mov esp, 0x105000

call load_idt

call init_pic

sti

call kernel_main

hlt_loop
hlt
jmp hlt_loop

