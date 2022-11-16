#include "../include/type.h"
#include "../include/config.h"

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

void init_pages(){
    uint64_t *p = (uint64_t *)(KINITPAGE_PHYADR);
    uint64_t *pdpte = (uint64_t *)(KINITPAGE_PHYADR + 0x1000);
    uint64_t *pde = (uint64_t *)(KINITPAGE_PHYADR + 0x2000);

    uint64_t adr = 0;

    for (uint_t mi = 0; mi < PG_ENTRY_SIZE; mi++)
    {
        p[mi] = 0;
        pdpte[mi] = 0;
    }
    for (uint_t pdei = 0; pdei < 16; pdei++)
    {
        pdpte[pdei] = (uint64_t) ((uint32_t)pde | KPDPTE_RW | KPDPTE_P);
        for (uint_t pdeii = 0; pdeii < PGENTY_SIZE; pdeii++)
        {
            pde[pdeii] = 0 | adr | KPDE_PS | KPDE_RW | KPDE_P;
            adr += 0x200000;
        }
        pde = (uint64_t *)((uint32_t)pde + 0x1000);
    }
    p[((KRNL_VIRTUAL_ADDRESS_START) >> KPML4_SHIFT) & 0x1ff] = (uint64_t) ((uint32_t)pdpte | KPML4_RW | KPML4_P);
    p[0] = (uint64_t) ((uint32_t)pdpte | KPML4_RW | KPML4_P);
    return;
}

void setup_main(){
    init_pages();
}

void setup_die(){
    char * video_mem = (char *) VIDEO_MEM;

    video_mem[0] = 'D';
    video_mem[1] = 15;

    video_mem[2] = 'I';
    video_mem[3] = 15;

    video_mem[4] = 'E';
    video_mem[5] = 15;
    while(1);
}