[BITS 32]
[SECTION .asm]
global load_idt
load_idt:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]

    pop ebp
    ret

