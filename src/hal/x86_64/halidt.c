#include "halidt.h"
#include "halglobal.h"
#include "../../include/memory.h"
#include "../../include/stdio.h"

idtr_desc_t idtr;

int_desc_t idt[IDT_MAX];

void set_idt(uint32_t i, uint8_t type, int_handler handler)
{
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

void idt0(){
    printk("Divide by zero");
    while(1);
}

void init_idt(){
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint64_t)idt;
    set_idt(INT_DESC_DIVIDE, INT_DPL_KERNEL|INT_GATE, idt0);
    set_idt(1, INT_DPL_KERNEL|INT_GATE, idt0);
    __asm__ __volatile__("lidt idtr");
}