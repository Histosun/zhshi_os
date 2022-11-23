[SECTION .text]
[BITS 64]

global load_idt

load_idt:
    push rbp
    mov rbp, rsp

    lidt [rdi]

    pop rbp
    ret