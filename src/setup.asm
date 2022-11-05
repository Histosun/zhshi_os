[BITS 32]
global _start

extern kernel_main

CODE_SEG equ 0x8
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call kernel_main

    jmp $

times 512 - ($ - $$) db 0