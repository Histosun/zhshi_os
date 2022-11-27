#include "../include/type.h"
#include "../include/config.h"
#include "../ldr/ldrtype.h"
#include "../ldr/ldr.h"

kernel_desc_t* kd;
void init_kernel(){
    kd = KERNEL_START;
    kd->kernel_start = KERNEL_START;
    kd->next_pg = P4K_ALIGN(KERNEL_START + kd->kernel_size + kd->offset);
}

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

int setup_main(){
    init_kernel();
    init_mach_param();
    init_pages();
}