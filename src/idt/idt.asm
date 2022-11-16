[SECTION .text]
[BITS 32]
global load_idt
load_idt:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]

    pop ebp
    ret

