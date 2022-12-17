#include "../include/stdio.h"
#include "../include/memory.h"
#include "../hal/x86_64/halinit.h"
#include "../hal/x86_64/halconsole.h"
#include "../hal/x86_64/halglobal.h"

__attribute__((section(".data"))) kernel_desc_t kernel_info;

void copy_kernel_desc(kernel_desc_t * p_kernel_desc) {
    kernel_desc_t * temp = (kernel_desc_t*)(KERNEL_START - KERNEL_OFF);
    memcpy(temp, p_kernel_desc, sizeof (kernel_desc_t));

    if(p_kernel_desc->kernel_magic != ZHOS_MAGIC){
        while (1);
    }
}

void kernel_main(){
    for(int i = 0; i < 1000000; ++i) {
        write_number(i);
    }
    copy_kernel_desc(&kernel_info);
    init_hal(&kernel_info);

//    __asm__("sti;");
    printk("Hello kernel!");
    while (1);
}