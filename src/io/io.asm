[SECTION .text]
global insb
global insw

insb:
    xor eax, eax
    in al, [esp+8]
    ret

insw:
    xor eax, eax
    in ax, [esp+8]
    ret