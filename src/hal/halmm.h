#ifndef HALMM_H
#define HALMM_H

#include "../include/type.h"
#include "../lib/spinlock.h"

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

typedef struct phymm
{
    spinlock_t pm_lock;     //spinlock
    uint32_t pm_type;       //memory address space type
    uint32_t pm_stype;
    uint32_t pm_dtype;      //Subtype of memory address space, see macro above
    uint32_t pm_flgs;       //Structure flags and states
    uint32_t pm_stus;
    uint64_t pm_saddr;      //start address of memory space
    uint64_t pm_lsize;      //The size of the memory space
    uint64_t pm_end;        //End address of memory space
    uint64_t pm_rvmsaddr;  //The starting address of the reserved memory space
    uint64_t pm_rvmend;    //End address of reserved memory space
    void* pm_prip;
    void* pm_extp;
}phymm_t;

void init_phymm();

#endif