#ifndef HAL_TYPE_H
#define HAL_TYPE_H

#include "../../include/type.h"
#include "../../include/btypeinc/spinlock.h"
#include "../../ldr/ldrtype.h"

#define IDT_MAX 256

typedef struct int_desc {
    uint16_t offset_0;  // Offset 0-15
    uint16_t selector;  // GDT selector
    uint8_t zero_1;     // Reserved, always set to zero
    uint8_t type;       // Type of the interrupt descriptor
    uint16_t offset_1;  // offset 16-31
    uint32_t offset_2;  // offset 32-63
    uint32_t  zero_2;
}__attribute__((packed)) int_desc_t;

typedef struct idtr_desc {
    uint16_t limit;     // Limit of IDT
    uint64_t base;      // Base address of IDT
}__attribute__((packed)) idtr_desc_t;

#endif