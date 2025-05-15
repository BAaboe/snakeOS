; Prints the character in ah, ah is not a pointer
bios_print_char:
mov ah, 0x0e
xor bx, bx
int 0x10
ret

; Prints a new line
bios_print_nl:
mov ah, 0x0e
mov al, 10
xor bx, bx
int 0x10

mov al, 13
int 0x10

; Print string until zero terminator. Pointer to first char in ax
bios_print:
mov bx, ax
_print_loop:
cmp byte [ bx ], 0
jz _print_ret

mov ah, 0x0e
mov al, byte [ bx ]
push bx
xor bx, bx
int 0x10
pop bx

inc bx
jmp _print_loop

_print_ret:
ret
