section .data
idt:
times 256 dq 0
idt_end:

idtr:
	dw 0
	dd 0
	


section .text
load_idt:
call populate_idt

xor eax, eax
mov eax, idt_end
sub eax, idt
dec eax
mov word [idtr], ax

xor eax, eax
mov ax, ds
shl eax, 4
mov eax, idt
mov [idtr + 2], eax

lidt [idtr]

ret

%macro set_interupt_handler 3
	mov eax, %3
	mov word [%1], ax

	mov ax, 0x8
	mov word [%1+2], ax

	mov byte [%1+4], 0

	mov al, %2
	mov al, 0x8e
	mov byte [%1+5], al

	shr eax, 16
	mov word [%1+6], ax
%endmacro

populate_idt:
set_interupt_handler idt+(8*0), 0xe, handle_de
set_interupt_handler idt+(8*1), 0xf, handle_exception
set_interupt_handler idt+(8*2), 0xe, handle_exception
set_interupt_handler idt+(8*3), 0xf, handle_exception
set_interupt_handler idt+(8*4), 0xf, handle_of
set_interupt_handler idt+(8*5), 0xe, handle_exception
set_interupt_handler idt+(8*6), 0xe, handle_exception
set_interupt_handler idt+(8*7), 0xe, handle_exception
set_interupt_handler idt+(8*8), 0xe, handle_exception
set_interupt_handler idt+(8*9), 0xe, handle_exception
set_interupt_handler idt+(8*10), 0xe, handle_exception
set_interupt_handler idt+(8*11), 0xe, handle_np
set_interupt_handler idt+(8*12), 0xe, handle_ss
set_interupt_handler idt+(8*13), 0xe, handle_exception
set_interupt_handler idt+(8*14), 0xe, handle_exception
set_interupt_handler idt+(8*16), 0xe, handle_exception
set_interupt_handler idt+(8*17), 0xe, handle_exception
set_interupt_handler idt+(8*18), 0xe, handle_exception
set_interupt_handler idt+(8*19), 0xe, handle_exception
set_interupt_handler idt+(8*20), 0xe, handle_exception
set_interupt_handler idt+(8*21), 0xe, handle_exception

; pic 1
set_interupt_handler idt+(8*32), 0x0e, handle_irq0
set_interupt_handler idt+(8*33), 0x0e, handle_pic1
set_interupt_handler idt+(8*34), 0x0e, handle_pic1
set_interupt_handler idt+(8*35), 0x0e, handle_pic1
set_interupt_handler idt+(8*36), 0x0e, handle_pic1
set_interupt_handler idt+(8*37), 0x0e, handle_pic1
set_interupt_handler idt+(8*38), 0x0e, handle_pic1
set_interupt_handler idt+(8*39), 0x0e, handle_pic1
; pic 2
set_interupt_handler idt+(8*40), 0x0e, handle_pic2
set_interupt_handler idt+(8*41), 0x0e, handle_pic2
set_interupt_handler idt+(8*42), 0x0e, handle_pic2
set_interupt_handler idt+(8*43), 0x0e, handle_pic2
set_interupt_handler idt+(8*44), 0x0e, handle_pic2
set_interupt_handler idt+(8*45), 0x0e, handle_pic2
set_interupt_handler idt+(8*46), 0x0e, handle_pic2
set_interupt_handler idt+(8*47), 0x0e, handle_pic2

ret

extern other_error
handle_exception:
call other_error
cli
hlt

iret

extern de
handle_de:
pusha

call de

cli
hlt
popa
iret

extern of
handle_of:
pusha

call of

popa
iret

extern np
handle_np:
pusha

call np

popa
iret

extern sse
handle_ss:
pusha

call sse

popa
iret

extern df
handle_df:
pusha

call df

popa
iret


extern time_tick
handle_irq0:
pusha

call time_tick

popa

jmp eoi1

extern handle_pic
handle_pic1:
pusha

call handle_pic

popa

mov al, 0x20
out 0x20, al
iret

handle_pic2:
jmp eoi2

eoi2:
mov al, 0x20
out 0xA0, al
eoi1:
mov al, 0x20
out 0x20, al
iret
