#include "halidt.h"
#include "../halglobal.h"
#include "../../../include/stdio.h"
#include "../halio.h"

extern void exc_divide_error();
extern void exc_default();

idtr_desc_t idtr;

int_desc_t idt[IDT_MAX];

void set_idt(uint32_t i, uint8_t type, int_handler handler) {
    int_desc_t * interrupt = &idt[i];
    uint64_t base = (uint64_t)handler;
    interrupt->offset_0 = base & 0xffff;
    interrupt->selector = SELECTOR_KERNEL_CS;
    interrupt->zero_1 = 0;
    interrupt->type = type;
    interrupt->offset_1 = (uint16_t)((base >> 16) & 0xffff);
    interrupt->offset_2 = (uint32_t)((base >> 32) & 0xffffffff);
    interrupt->zero_2 = 0;
    return;
}

void load_idt(idtr_desc_t *idtptr) {
    __asm__ __volatile__(
            "lidt (%0)"
            :
            : "r"(idtptr)
            : "memory");
    return;
}

//For now hard coded. Will use macro to replace it in future
void init_8259a(){
    out_byte(0x20, 0x11);
    out_byte(0xA0, 0x11);
    out_byte(0x21, 0x20);
    out_byte(0xA1, 0x28);
    out_byte(0x21, 0x4);
    out_byte(0xA1, 0x2);
    out_byte(0x21, 0x3);
    out_byte(0xA1, 0x3);

    out_byte(0x21, 0xfd);
    out_byte(0xA1, 0xff);
}

void init_idt(){
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint64_t)idt;
    set_idt(INT_DESC_DIVIDE, INT_DPL_KERNEL|INT_GATE, exc_divide_error);
    set_idt(1, INT_DPL_KERNEL|INT_GATE, exc_divide_error);
    init_8259a();
    set_idt(0x21, INT_DPL_KERNEL|INT_GATE, exc_default);
    load_idt(&idtr);
}