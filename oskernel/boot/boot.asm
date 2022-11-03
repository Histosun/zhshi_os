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
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov sp, 0x7c00
    sti

.to_protected_mode:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:protected_entrance

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

[BITS 32]
protected_entrance:
    mov ebx, 1
    mov ecx, 100
    mov edi, 0x100000
    call ata_lba_read
    jmp CODE_SEG:0x100000

ata_lba_read:
    mov eax, ebx
    ; LBA low
    mov dx, 0x1f3
    out dx, al

    ; LBA mid
    mov dx, 0x1f4
    shr eax, 8
    out dx, al

    ; LBA high
    mov dx, 0x1f5
    shr eax, 16
    out dx, al

    mov dx, 0x1f6
    shr eax, 8
    and al, 0x0f
    or al, 0xe0
    out dx, al
    
    mov dx, 0x1f7
    mov al, 0x20
    out dx, al


.next_sector:
    push ecx


    mov dx, 0x1f7
.check_hd:
    in al, dx
    test al, 8
    jz .check_hd

.read_hd:
    mov ecx, 256
    mov dx, 0x1f0
    rep insw

    pop ecx
    loop .next_sector

    ret

times 510 - ($ - $$) db 0
db 0x55, 0xaa