#ifndef HAL_TYPE_H
#define HAL_TYPE_H

#include "../../include/type.h"
#include "../../lib/spinlock.h"

typedef struct krl_mach
{
    uint64_t zhos_magic;    //magic of zhos
    uint64_t init_stack;    //kernel stack address
    uint64_t stack_sz;      //kernel stack size
    uint64_t cpu_mode;      //cpu mode
    uint64_t mach_memsize;    //memory size of machine
} krl_mach_t;

#define PMR_T_OSAPUSERRAM 1
#define PMR_T_RESERVRAM 2
#define PMR_T_HWUSERRAM 8
#define PMR_T_ARACONRAM 0xf
#define PMR_T_BUGRAM 0xff
#define PMR_F_X86_32 (1<<0)
#define PMR_F_X86_64 (1<<1)
#define PMR_F_ARM_32 (1<<2)
#define PMR_F_ARM_64 (1<<3)
#define PMR_F_HAL_MASK 0xff

typedef struct phy_memory
{
    spinlock_t pm_lock;     //spinlock that protect the struct
    uint32_t pm_type;       //memory address space type
    uint32_t pm_stype;
    uint32_t pm_dtype;      //Subtype of memory address space, see macro above
    uint32_t pm_flgs;       //Structure flags and states
    uint32_t pm_stus;
    uint64_t pm_saddr;      //start address of memory space
    uint64_t pm_lsize;      //The size of the memory space
    uint64_t pm_end;        //End address of memory space
    uint64_t pm_rsvmsaddr;  //The starting address of the reserved memory space
    uint64_t pm_rsvmend;    //End address of reserved memory space
    void* pm_prip;
    void* pm_extp;
}phy_memory_t;

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