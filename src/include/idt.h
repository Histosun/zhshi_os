#ifndef IDT_H
#define IDT_H
#include "type.h"

#define IDT_MAX 512

typedef struct int_desc {
    uint16_t offset_0;  // Offset 0-15
    uint16_t selector;  // GDT selector
    uint8_t zero;       // Reserved, always set to zero
    uint8_t type;       // Type of the interrupt descriptor
    uint16_t offset_1;  // offset 0-32
}__attribute__((packed)) int_desc_t;

typedef struct idtr_desc {
    uint16_t limit;     // Limit of IDT
    uint32_t base;      // Base address of IDT
}__attribute__((packed)) idtr_desc_t;

void idt_init();
#endif