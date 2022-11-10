#include "../include/type.h"

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

void setup_main(){
    e820_desc_t * mem = (e820_desc_t *)E820_DESC;

    char * video_mem = (char *) VIDEO_MEM;

    video_mem[0] = 'B';
    video_mem[1] = 15;
}