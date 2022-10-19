ORG 0x0
BITS 16

_start:
    jmp short start
    nop
    times 0x21 db 0

start:
    cli
    mov     ax, 0x7c0
    mov     ss, ax
    mov     ds, ax
    mov     es, ax
    sti

    mov si, message
    call print

    jmp $

print:
    mov ah, 0x0e
    mov bh, 0
    mov bl, 0x01
.loop:
    lodsb
    cmp al, 0
    jz .done
    int 0x10
    jmp .loop
    
.done:
    ret

message:
    db "Hello world!", 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa