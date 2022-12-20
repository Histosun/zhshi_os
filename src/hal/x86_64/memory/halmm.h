#ifndef HAL_MM_H
#define HAL_MM_H

#include "../../../include/type.h"
#include "../../../include/btypeinc/spinlock.h"
#include "../haltype.h"

#define RAM_USABLE 1
#define RAM_RESERV 2
#define RAM_ACPIREC 3
#define RAM_ACPINVS 4
#define RAM_AREACON 5

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

typedef struct phymem_desc {
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
} phymem_desc_t;

void init_halmm(kernel_desc_t * p_kernel_desc);

#endif