#include "../include/idt.h"
#include "../include/mem.h"
#include "../include/config.h"

int_desc_t int_descriptors[IDT_MAX];
idtr_desc_t idtr_descriptor;

extern void load_idt(idtr_desc_t* ptr);

void idt_0(){

    char * video_mem = (char *) 0xB8000;

    video_mem[2] = 'C';
    video_mem[3] = 15;
}

void set_idt(int i, void* address){
    int_descriptors[i].zero=0;
    int_descriptors[i].offset_0=(uint32_t) address & 0x0000ffff;
    int_descriptors[i].selector=KERNEL_CODE_SELECTOR;
    int_descriptors[i].type=0xee;
    int_descriptors[i].zero=0;
    int_descriptors[i].offset_1=((uint32_t) address) >> 16;
}

void init_idt(){
    memset(int_descriptors, 0, sizeof(int_descriptors));
    idtr_descriptor.limit=sizeof(int_descriptors)-1;
    idtr_descriptor.base=(uint32_t)int_descriptors;

    idtr_desc_t* desc = &idtr_descriptor;
    load_idt(&idtr_descriptor);
    idt_set(0, &idt_0);
}