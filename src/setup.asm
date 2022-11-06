[BITS 32]
global _start

extern kernel_main

CODE_SEG equ 0x8
DATA_SEG equ 0x10

_start:
    cli
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x9fc00

    call kernel_main

    jmp $

times 512 - ($ - $$) db 0