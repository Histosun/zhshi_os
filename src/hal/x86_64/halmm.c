#include "halmm.h"
#include "halmm_t.h"
#include "halinit.h"
#include "halconsole.h"
#include "../../include/stdio.h"
#include "../../include/memory.h"


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

void sort_phymm(phymem_desc_t * phymm_arr, uint64_t num) {
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

void init_phymm(kernel_desc_t * p_kernel_desc) {
    if(p_kernel_desc->mmap_adr == 0 || p_kernel_desc->mmap_nr == 0){
        printk("e820 array error!");
        while (1);
    }
    uint64_t temp = p_kernel_desc->next_pg;
    phymem_desc_t * phymm = (phymem_desc_t *)temp;
    e820_map_t * e8p = (e820_map_t *)p_kernel_desc->mmap_adr;
    for(int i=0; i < p_kernel_desc->mmap_nr; ++i){
        if(set_phymem_desc(&e8p[i], &phymm[i]) == FALSE){
            printk("Error occurs when setting memory address");
            while(1);
        }
    }
    p_kernel_desc->mmap_adr = (uint64_t)phymm;
    p_kernel_desc->mmap_sz = p_kernel_desc->mmap_nr * sizeof(phymem_desc_t);
    sort_phymm(phymm, p_kernel_desc->mmap_nr);
    p_kernel_desc->next_pg = P4K_ALIGN(temp + p_kernel_desc->mmap_nr * sizeof(phymem_desc_t));
}

bool_t ret_mpdesc_adrandsz(kernel_desc_t * p_kernel_desc, mpgdesc_t** p_mpdesc_arr, uint64_t * p_mpdescnr) {
    if(p_kernel_desc == NULL || p_mpdesc_arr == NULL || p_mpdescnr == NULL) {
        return FALSE;
    }
    if(p_kernel_desc->mmap_nr < 1 || p_kernel_desc->mmap_adr == 0 || p_kernel_desc->mmap_sz != p_kernel_desc->mmap_nr * sizeof(phymem_desc_t)) {
        return FALSE;
    }
    phymem_desc_t * phymem_arr = p_kernel_desc->mmap_adr;
    uint64_t umemsz = 0, mpdescnr = 0;
    for(int i = 0; i < p_kernel_desc->mmap_nr; ++i){
        if(phymem_arr[i].pm_type == PMR_T_OSAPUSERRAM){
            umemsz += phymem_arr[i].pm_lsize;
            mpdescnr += (phymem_arr[i].pm_lsize >> 12);
        }
    }
    if((umemsz >> 12) < 1 || mpdescnr < 1){
        return FALSE;
    }
    *p_mpdesc_arr = p_kernel_desc->next_pg;
    *p_mpdescnr = mpdescnr;
    return TRUE;
}

void set_mpdesc(mpgdesc_t * mpdesc, uint64_t phy_adr) {
    mpdesc_t_init(mpdesc);
    phyadrflgs_t *tmp = (phyadrflgs_t *)(&phy_adr);
    mpdesc->mp_phyadr.paf_phyadr = tmp->paf_phyadr;
}

uint64_t init_mpdesc_core(kernel_desc_t * p_kernel_desc, mpgdesc_t * mpdesc_arr) {
    phymem_desc_t * pm_arr = p_kernel_desc->mmap_adr;
    uint64_t mpnr = 0;
    for(int i = 0; i < p_kernel_desc->mmap_nr; ++i){
        if(pm_arr[i].pm_type == PMR_T_OSAPUSERRAM) {
            for(uint64_t mp_adr = pm_arr[i].pm_saddr; mp_adr < pm_arr[i].pm_end; mp_adr += 4096 ){
                if(mp_adr + 4096 - 1 <= pm_arr[i].pm_end) {
                    set_mpdesc(&mpdesc_arr[mpnr], mp_adr);
                    ++mpnr;
                }
            }
        }
    }
    return mpnr;
}

void init_mpdesc(kernel_desc_t * p_kernel_desc){
    uint64_t coremdnr = 0, mpdescnr = 0;
    mpgdesc_t * mpdesc_arr = NULL;

    if(!ret_mpdesc_adrandsz(p_kernel_desc, &mpdesc_arr, &mpdescnr)) {
        printk("init_memmanager ret_mpdesc_adrandsz error!");
        while(1);
    }
    coremdnr = init_mpdesc_core(p_kernel_desc, mpdesc_arr);
    if(coremdnr != mpdescnr){
        printk("init_memmanager init_mpdesc_core error!");
        while(1);
    }
    p_kernel_desc->mp_desc_arr = mpdesc_arr;
    p_kernel_desc->mp_desc_nr = coremdnr;
    p_kernel_desc->mp_desc_sz = sizeof(mpgdesc_t) * coremdnr;
    p_kernel_desc->next_pg = P4K_ALIGN(p_kernel_desc->next_pg + p_kernel_desc->mp_desc_sz);
}

void init_memarea(kernel_desc_t * p_kernel_desc){

}

void init_memmanager(kernel_desc_t * p_kernel_desc) {
    init_mpdesc(p_kernel_desc);
    init_memarea(p_kernel_desc);
}

void init_halmm(kernel_desc_t * p_kernel_desc) {
    init_phymm(p_kernel_desc);
    init_memmanager(p_kernel_desc);
}