#include "halinit.h"
#include "memory/halmm.h"
#include "halconsole.h"
#include "interrupt/halidt.h"

void init_hal(kernel_desc_t * p_kernel_desc){
    init_idt();
    init_halmm(p_kernel_desc);
    init_console();
    return;
}