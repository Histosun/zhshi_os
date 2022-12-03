#include "../hal/x86_64/halinit.h"
#include "../include/stdio.h"

void kernel_main(){
    init_hal();

    __asm__("sti;");
    printk("Hello kernel!");
//    while (1);
}