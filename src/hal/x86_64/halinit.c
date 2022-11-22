#include "halinit.h"
#include "halmm.h"
#include "halconsole.h"
#include "halidt.h"
#include "../../ldr/ldrtype.h"
#include "../../include/memory.h"

void init_hal(){
//    init_mach();
    init_idt();
    init_console();
    return;
}

void init_mach(){
    krlmach_info_t * krlmachInfo = MIPADR;
    memset(&kmach, 0, sizeof(kmach));
    kmach.zhos_magic = krlmachInfo->zhos_magic;
    kmach.init_stack = krlmachInfo->init_stack;
    kmach.stack_sz = krlmachInfo->stack_sz;
    kmach.cpu_mode = krlmachInfo->cpu_mode;
    kmach.mach_memsize = krlmachInfo->mach_memsize;


}