#ifndef HAL_GLOBAL_H
#define HAL_GLOBAL_H
#include "haltype.h"

#define SELECTOR_KERNEL_CS 0x8
#define SELECTOR_KERNEL_DS 0x10
#define PAGE_SHR 12
#define PAGE_SIZE (0x1UL<<PAGE_SHR)
#define HAL_DEFGLOB_VARIABLE(vartype,varname) __attribute__((section(".data"))) vartype varname

#endif