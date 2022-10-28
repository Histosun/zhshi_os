ORG 0x500
BITS 16

_start:
    cli
    mov     ax, 0x0
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
    db "Setup Hello world!", 0