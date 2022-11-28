#include "halmm.h"
#include "halinit.h"
#include "../../include/stdio.h"
#include "../../lib/memory.h"


void init_one_phymm(phymem_desc_t * initp){
    if (NULL == initp)
    {
        return;
    }
    initp->pm_lock.lock = 0;
    initp->pm_type = 0;
    initp->pm_stype = 0;
    initp->pm_dtype = 0;
    initp->pm_flgs = 0;
    initp->pm_stus = 0;
    initp->pm_saddr = 0;
    initp->pm_lsize = 0;
    initp->pm_end = 0;
    initp->pm_rsvmend = 0;
    initp->pm_rsvmend = 0;
    initp->pm_prip = NULL;
    initp->pm_extp = NULL;
    return;

}

int set_phymem_desc(e820_map_t * e8p, phymem_desc_t * phymm){
    uint32_t ptype = 0, pstype = 0;
    if (NULL == e8p || NULL == phymm)
    {
        return FALSE;
    }
    init_one_phymm(phymm);
    switch (e8p->type)
    {
        case RAM_USABLE:
            ptype = PMR_T_OSAPUSERRAM;
            pstype = RAM_USABLE;
            break;
        case RAM_RESERV:
            ptype = PMR_T_RESERVRAM;
            pstype = RAM_RESERV;
            break;
        case RAM_ACPIREC:
            ptype = PMR_T_HWUSERRAM;
            pstype = RAM_ACPIREC;
            break;
        case RAM_ACPINVS:
            ptype = PMR_T_HWUSERRAM;
            pstype = RAM_ACPINVS;
            break;
        case RAM_AREACON:
            ptype = PMR_T_BUGRAM;
            pstype = RAM_AREACON;
            break;
        default:
            break;
    }
    if (0 == ptype)
    {
        return FALSE;
    }
    phymm->pm_type = ptype;
    phymm->pm_stype = pstype;
    phymm->pm_flgs = PMR_F_X86_64;
    phymm->pm_saddr = e8p->addr;
    phymm->pm_lsize = e8p->size;
    phymm->pm_end = e8p->addr + e8p->size - 1;
    return TRUE;

}

void phymm_swap(phymem_desc_t *s, phymem_desc_t *d)
{
    phymem_desc_t tmp;
    init_one_phymm(&tmp);
    memcpy(s, &tmp, sizeof(phymem_desc_t));
    memcpy(d, s, sizeof(phymem_desc_t));
    memcpy(&tmp, d, sizeof(phymem_desc_t));
    return;
}

void sort_phymm(phymem_desc_t * phymm_arr, uint64_t num){
    uint64_t i, j, k = num - 1;
    for (j = 0; j < k; j++) {
        for (i = 0; i < k - j; i++) {
            if (phymm_arr[i].pm_saddr > phymm_arr[i + 1].pm_saddr) {
                phymm_swap(&phymm_arr[i], &phymm_arr[i + 1]);
            }
        }
    }
    return;
}

void init_phymm(kernel_desc_t * p_kernel_desc){
    uint64_t temp = p_kernel_desc->next_descriptor_addr;
    p_kernel_desc->next_descriptor_addr = ALIGN(temp + p_kernel_desc->mmap_nr * sizeof(phymem_desc_t), 8);
    if(p_kernel_desc->next_descriptor_addr >= p_kernel_desc->kernel_start){
        printk("Not enough memory for descriptors!");
        while(1);
    }
    phymem_desc_t * phymm = (phymem_desc_t *)temp;
    e820_map_t * e8p = (e820_map_t *)p_kernel_desc->mmap_adr;
    for(int i=0; i < p_kernel_desc->mmap_nr; ++i){
        printk("%d", phymm[i].pm_saddr);
        if(set_phymem_desc(&e8p[i], &phymm[i]) == FALSE){
            printk("Error occurs when setting memory address");
            while(1);
        }
    }
    p_kernel_desc->mmap_adr = (uint64_t)phymm;
    p_kernel_desc->mmap_sz = p_kernel_desc->mmap_nr * sizeof(phymem_desc_t);
    sort_phymm(phymm, p_kernel_desc->mmap_nr);
}