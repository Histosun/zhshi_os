#include "halinit.h"
#include "halmm.h"
#include "halconsole.h"
#include "interrupt/halidt.h"

void init_hal(){
    pkernel_des = (kernel_desc_t*)KERNEL_START;
    init_idt();
//    init_halmm(pkernel_des);
    init_console();
    return;
}