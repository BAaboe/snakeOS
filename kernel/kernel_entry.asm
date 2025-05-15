[BITS 32]

[global kernel]
[extern main]

kernel:
; Setting up the segments
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
mov esp, 0x105000

call main

hlt
