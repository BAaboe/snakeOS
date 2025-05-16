idt:
times 256 dq 0
idt_end:

idtr:
	dw 0
	dd 0
	
section .text

extern putstring

load_idt:
xor eax, eax
mov eax, idt_end
sub eax, idt
mov word [idtr], ax

xor eax, eax
mov ax, ds
shl eax, 4
mov eax, idt
mov [idtr + 2], eax

; TODO: Fix PIC
lidt [idtr]

sti

ret

%macro set_exception_handler 2
	mov eax, handle_exception
	mov word [%1], ax

	mov ax, 0x0008
	mov word [%1+2], ax

	mov byte [%1-4], 0

	mov al, %2
	or al, 0x80
	mov byte [%1+5], al

	shr eax, 16
	mov word [%1+6], ax
%endmacro

populate_idt:
set_exception_handler idt+(8*0), 0xf
set_exception_handler idt+(8*1), 0xf
set_exception_handler idt+(8*2), 0xe
set_exception_handler idt+(8*3), 0xf
set_exception_handler idt+(8*4), 0xf
set_exception_handler idt+(8*5), 0xf
set_exception_handler idt+(8*6), 0xf
set_exception_handler idt+(8*7), 0xf
set_exception_handler idt+(8*8), 0xf
set_exception_handler idt+(8*9), 0xf
set_exception_handler idt+(8*10), 0xf
set_exception_handler idt+(8*11), 0xf
set_exception_handler idt+(8*12), 0xf
set_exception_handler idt+(8*13), 0xf
set_exception_handler idt+(8*14), 0xf
set_exception_handler idt+(8*16), 0xf
set_exception_handler idt+(8*17), 0xf
set_exception_handler idt+(8*18), 0xf
set_exception_handler idt+(8*19), 0xf
set_exception_handler idt+(8*20), 0xf
set_exception_handler idt+(8*21), 0xf

ret

handle_exception:
hlt
iret
