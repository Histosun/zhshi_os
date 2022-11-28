#ifndef HAL_TYPE_H
#define HAL_TYPE_H

#include "../../include/type.h"
#include "../../lib/spinlock.h"
#include "../../ldr/ldrtype.h"

kernel_desc_t * pkernel_des;

#define IDT_MAX 256

typedef struct int_desc {
    uint16_t offset_0;  // Offset 0-15
    uint16_t selector;  // GDT selector
    uint8_t zero_1;       // Reserved, always set to zero
    uint8_t type;       // Type of the interrupt descriptor
    uint16_t offset_1;  // offset 0-32
    uint32_t offset_2;
    uint32_t  zero_2;
}__attribute__((packed)) int_desc_t;

typedef struct idtr_desc {
    uint16_t limit;     // Limit of IDT
    uint64_t base;      // Base address of IDT
}__attribute__((packed)) idtr_desc_t;

#endif