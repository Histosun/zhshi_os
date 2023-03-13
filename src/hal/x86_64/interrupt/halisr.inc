%define NO_ERROR_CODE 0xffffffffffffffff
%macro SAVE_ALL	0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi

    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    xor r14, r14
    mov r14w, ds
    push r14
    mov r14w, es
    push r14
    mov r14w, fs
    push r14
    mov r14w, gs
    push r14
%endmacro

%macro RESTORE_ALL 0
    pop r14
    mov gs, r14w
    pop r14
    mov fs, r14w
    pop r14
    mov es, r14w
    pop r14
    mov ds, r14w

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8

    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro ISR_FAULT 1
    SAVE_ALL
    mov r14w,0x10
    mov ds,r14w
    mov es,r14w
    mov fs,r14w
    mov gs,r14w

    call %1

    RESTORE_ALL
    iretq
%endmacro

%macro ISR_ERROR_FAULT 1
    SAVE_ALL
    mov r14w, 0x10
    mov ds, r14w
    mov es, r14w
    mov fs, r14w
    mov gs, r14w

    call %1

    RESTORE_ALL
    add rsp,8
    iretq
%endmacro

%macro ISR_ERROR_DEFAULT 1
    SAVE_ALL
    mov r14w, 0x10
    mov ds, r14w
    mov es, r14w
    mov fs, r14w
    mov gs, r14w

    mov rdi, %1
    call default_handler

    RESTORE_ALL
    add rsp, 8
    iretq
%endmacro

%macro ISR_DEFAULT 1
    SAVE_ALL
    mov r14w,0x10
    mov ds,r14w
    mov es,r14w
    mov fs,r14w
    mov gs,r14w

    mov rdi, %1
    call default_handler

    RESTORE_ALL
    iretq
%endmacro