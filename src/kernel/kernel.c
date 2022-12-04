#include "../hal/x86_64/halinit.h"
#include "../include/stdio.h"
#include "../include/memory.h"

kernel_desc_t kernel_desc;

void copy_kernel_desc(kernel_desc_t * p_kernel_desc) {
    kernel_desc_t * temp = (kernel_desc_t*)(KERNEL_START - KERNEL_OFF);
    memcpy(temp, &kernel_desc, sizeof (kernel_desc_t));

    if(kernel_desc.kernel_magic != ZHOS_MAGIC){
        while (1);
    }
}

void kernel_main(){
    copy_kernel_desc(&kernel_desc);

    init_hal(&kernel_desc);

//    __asm__("sti;");
    printk("Hello kernel! %d", kernel_desc.mp_desc_nr);
    while (1);
}