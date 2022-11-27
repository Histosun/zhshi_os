#include "../hal/x86_64/halinit.h"
#include "../include/stdio.h"

void kernel_main(){
    init_hal();
    printk("Hello kernel!");
//    char * video_mem = (char *) VIDEO_MEM;
//    e820_desc_t* e820_descriptor = (e820_desc_t *)(KRNL_VIRTUAL_ADDRESS_START+E820_DESC);
//    if(e820_descriptor->e820_num==6){
//        video_mem[0] = 'K';
//        video_mem[1] = 15;
//    }

//    __asm__("sti;");

    while (1);
}