#include "../include/type.h"
#include "../include/config.h"
//#include "../hal/halinit.h"
#define VIDEO_MEM 0xB8000

#define E820_DESC 0x5000
#define E820_MAX 200

typedef struct e820_map {
    uint64_t addr;
    uint64_t size;
    uint32_t type;
}__attribute__((packed)) e820_map_t;

typedef struct e820_desc {
    uint32_t e820_num;
    e820_map_t maps[E820_MAX];
}__attribute__((packed)) e820_desc_t;

void kernel_main(){
//    init_hal();
    char * video_mem = (char *) VIDEO_MEM;
    e820_desc_t* e820_descriptor = (e820_desc_t *)(KRNL_VIRTUAL_ADDRESS_START+E820_DESC);
    if(e820_descriptor->e820_num==6){
        video_mem[0] = 'K';
        video_mem[1] = 15;
    }
}