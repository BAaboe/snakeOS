[BITS 32]

[global kernel]
[extern kernel_main]

kernel:
; Setting up the segments
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
mov esp, 0x105000

call kernel_main

hlt
