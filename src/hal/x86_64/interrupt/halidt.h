#ifndef HAL_IDT_H
#define HAL_IDT_H
#include "../haltype.h"

#define	INT_DESC_DIVIDE 0x0
#define	INT_DESC_DEBUG 0x1
#define	INT_DESC_NMI 0x2
#define	INT_DESC_BREAKPOINT 0x3
#define	INT_DESC_OVERFLOW 0x4
#define	INT_DESC_BOUNDS 0x5
#define	INT_DESC_INVAL_OP 0x6
#define	INT_DESC_COPROC_NOT 0x7
#define	INT_DESC_DOUBLE_FAULT 0x8
#define	INT_DESC_COPROC_SEG 0x9
#define	INT_DESC_INVAL_TSS 0xA
#define	INT_DESC_SEG_NOT 0xB
#define	INT_DESC_STACK_FAULT 0xC
#define	INT_DESC_PROTECTION 0xD
#define	INT_DESC_PAGE_FAULT 0xE
#define	INT_DESC_COPROC_ERR 0x10
#define	INT_DESC_ALIGN_CHEK 0x11
#define	INT_DESC_MACHI_CHEK 0x12
#define	INT_DESC_SIMD_FAULT 0x13

typedef void (*int_handler) ();

#define INT_DPL_KERNEL 0x80
#define INT_GATE 0x8E

void init_idt();
#endif