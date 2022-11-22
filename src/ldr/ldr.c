#include "ldr.h"

#define VIDEO_MEM 0xB8000

void die(){
    char * video_mem = (char *) VIDEO_MEM;

    video_mem[0] = 'D';
    video_mem[1] = 15;

    video_mem[2] = 'I';
    video_mem[3] = 15;

    video_mem[4] = 'E';
    video_mem[5] = 15;
    while(1);
}

void krl_mach_init(krlmach_info_t* pmach){
    char*ptr=pmach;
    for(int i=0; i<sizeof(krlmach_info_t);++i){
        *ptr = 0;
    }
    pmach->zhos_magic = ZHOS_MAGIC;
}

void* chk_memsize(e820_map_t *e8p, uint64_t e820_num, uint64_t sadr, uint64_t size){
    uint64_t eadr = sadr + size;
    if (e820_num == 0 || e8p == NULL)
    {
        return NULL;
    }
    for (uint32_t i = 0; i < e820_num; ++i)
    {
        if (e8p[i].type == RAM_USABLE)
        {
            if ((sadr >= e8p[i].addr) && (eadr < (e8p[i].addr + e8p[i].size)))
            {
                return &e8p[i];
            }
        }
    }
    return NULL;
}

uint64_t get_memsize(e820_desc_t * e820_desc){
    uint64_t size = 0;
    for(int i=0; i < e820_desc->e820_num; ++i){
        if(e820_desc->maps[i].type == RAM_USABLE) {
            size += e820_desc->maps[i].size;
        }
    }
    return size;
}

void krl_mach_mmap(krlmach_info_t* pmach){
    e820_desc_t* e820_desc = (e820_desc_t*)E820_DESC;
    if(e820_desc->e820_num==0){
        die();
    }
    if(chk_memsize(e820_desc->maps, e820_desc->e820_num, 0x100000, 0x8000000) == NULL){
        die();
    }
    pmach->e820_adr = (uint64_t)e820_desc->maps;
    pmach->e820_nr = (uint64_t)e820_desc->e820_num;
    pmach->e820_sz = (uint64_t)(e820_desc->e820_num * sizeof(e820_map_t));
    pmach->mach_memsize = get_memsize(e820_desc);
}

void krl_mach_stack(krlmach_info_t* pmach){
    pmach->init_stack = IKSTACK_PHYADR;
    pmach->init_stack = IKSTACK_SIZE;
}

//init machine info
void init_mach_param() {
    krlmach_info_t* krlmachInfo = MIPADR;
    krl_mach_init(krlmachInfo);
    krl_mach_mmap(krlmachInfo);
    krl_mach_stack(krlmachInfo);
}