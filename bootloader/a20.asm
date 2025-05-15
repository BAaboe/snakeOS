; A20

a20_fail_message: db "The A20 line could not be enabled.", 0


check_a20:
; Checking if it is enabled

xor ax, ax
mov ds, ax

not ax
mov es, ax

mov si, 0x7DFE
mov di, 0x7E0E

mov al, byte [ds:si]
mov ah, byte [es:di]

push ax

mov byte [ds:si], 0x00
mov byte [es:di], 0xFF

cmp byte [ds:si], 0xFF

pop ax
mov byte [ds:si], al
mov byte [es:di], ah

mov ax, 0
jne check_a20_done
mov ax, 1

check_a20_done:
ret


enable_a20:
; Check if enabled
call check_a20_done
cmp ax, 0
jnz a20_done

; Try to enable with bios
mov ax, 2401h
int 15h

; Test if it worked
call check_a20_done
cmp ax, 0
jnz a20_done

; Try to enable with fast A20 gate
in al, 0x92
or al, 2
out 0x92, al

; Test if it worked
call check_a20_done
cmp ax, 0
jnz a20_done

mov ax, a20_fail_message
call bios_print
call bios_print_nl

a20_done:
ret

