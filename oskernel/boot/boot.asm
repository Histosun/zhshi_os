ORG 0x7c00
BITS 16


[SECTION .data]
BOOT_MAIN_ADDR equ 0x500

[SECTION .text]
_start:
    jmp short start
    nop
    times 0x21 db 0

start:
    ; clean screen
    mov ax, 3
    int 0x10
    
    cli
    mov ax, 0x0
    mov ss, ax
    mov ds, ax
    mov es, ax
    sti

    ; LBA adress
    mov ecx, 2
    ; amount of sector to be read
    mov bl, 2

    mov dx, 0x1f2
    mov al, bl
    out dx, al

    ; 0x1f3 LBA address low 8 bits
    inc dx
    mov al, cl
    out dx, al

    ; 0x1f4 LBA address mid 8 bits
    inc dx
    mov al, ch
    out dx, al

    ; 0x1f5 LBA address high 8 bits
    inc dx
    shr ecx, 16
    mov al, cl
    out dx, al

    ; 0x1f6 device head
    inc dx
    mov al, ch
    and al, 0xef
    out dx, al
    
    inc dx
    mov al, 0x20
    out dx, al

.read_check:
    mov dx, 0x1f7
    in al, dx
    and al, 0x88
    cmp al, 0x08
    jnz .read_check

.read_data:
    mov dx, 0x1f0
    mov cx, 256
    mov edi, BOOT_MAIN_ADDR

.read:
    in ax, dx
    mov [edi], ax
    add edi, 2
    loop .read

;;;;;;;;;;;;;
    mov si, message
    call print

    jmp 0x0:BOOT_MAIN_ADDR

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
    db "Switch to setup", 10, 13, 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa