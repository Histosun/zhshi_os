ORG 0x7c00

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[section .text]
[BITS 16]
_start:
    jmp short start
    nop
    times 0x21 db 0

start:
    cli
    mov     ax, 0
    mov     ss, ax
    mov     ds, ax
    mov     es, ax
    sti

.to_protected_mode:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp $

    
    ;jmp CODE_SEG:protected_entrance

gdt_start:
gdt_null:
    dd 0x0
    dd 0x0
gdt_code:   ; cs point to this
    dw 0xffff   ; Limit 0-15
    dw 0x0      ; Base 0-15
    db 0x0      ; Base 16-23
    db 0x9a     ; Access byte
    db 0xcf     ; flags and limit 16-19
    db 0x0      ; Base 23-31
gdt_data:   ; ds, ss, fs, gs point to this
    dw 0xffff   ; Limit 0-15
    dw 0x0      ; Base 0-15
    db 0x0      ; Base 16-23
    db 0x92     ; Access byte
    db 0xcf     ; flags and limit 16-19
    db 0x0      ; Base 23-31
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

print:
    mov ah, 0x0e

times 510 - ($ - $$) db 0
db 0x55, 0xaa