#include "halmm_t.h"

void mpgdesc_t_init(mpgdesc_t * mpgdesc){
    list_t_init(&mpgdesc->mp_list);
    mpgdesc->mp_lock.lock = 0;
    mpgdesc->mp_flgs.mf_olkty = MF_OLKTY_INIT;
    mpgdesc->mp_flgs.mf_lstty = MF_LSTTY_LIST;
    mpgdesc->mp_flgs.mf_mocty = MF_MOCTY_FREE;
    mpgdesc->mp_flgs.mf_marty = MF_MARTY_INIT;
    mpgdesc->mp_flgs.mf_uindx = MF_UINDX_INIT;

    mpgdesc->mp_phyadr.paf_alloc = PAF_NO_ALLOC;
    mpgdesc->mp_phyadr.paf_shared = PAF_NO_SHARED;
    mpgdesc->mp_phyadr.paf_swap = PAF_NO_SWAP;
    mpgdesc->mp_phyadr.paf_cache = PAF_NO_CACHE;
    mpgdesc->mp_phyadr.paf_kmap = PAF_NO_KMAP;
    mpgdesc->mp_phyadr.paf_loc = PAF_NO_LOCK;
    mpgdesc->mp_phyadr.paf_dirty = PAF_NO_DIRTY;
    mpgdesc->mp_phyadr.paf_busy = PAF_NO_BUSY;
    mpgdesc->mp_phyadr.paf_rsv = PAF_RSV_VAL;
    mpgdesc->mp_phyadr.paf_phyadr = PAF_INIT_PADRS;
    mpgdesc->mp_odlink = NULL;
}

void mpafhlst_t_init(mpafhlst_t * p_mpafhlst, uint32_t stus, uint_t oder){
    p_mpafhlst->af_lock.lock = 0;
    p_mpafhlst->af_stus = stus;
    p_mpafhlst->af_oder = oder;
    p_mpafhlst->af_oderpnr = 1UL << oder;
    p_mpafhlst->af_fobjnr = 0;
    p_mpafhlst->al_mobjnr = 0;
    p_mpafhlst->af_freindx = 0;
    p_mpafhlst->af_alcindx = 0;

    list_t_init(&p_mpafhlst->af_alclst);
    list_t_init(&p_mpafhlst->af_frelst);
}

void memdivmer_t_init (memdivmer_t * p_memdivmer) {
    p_memdivmer->dm_lock.lock = 0;
    p_memdivmer->dm_stus = 0;
    p_memdivmer->dm_divnr = 0;
    p_memdivmer->dm_mernr = 0;

    for(int i =0 ;i< MDIVMER_ARR_LMAX; ++i) {
        mpafhlst_t_init(&p_memdivmer->dm_mdmlielst[i], BAFH_STUS_DIVM, i);
    }

    mpafhlst_t_init(&p_memdivmer->dm_onemsalst, BAFH_STUS_ONEM, 0);
}

void memarea_t_init(memarea_t * p_memarea) {
    list_t_init(& p_memarea->ma_list);

    p_memarea->ma_lock.lock = 0;
    p_memarea->ma_stus = 0;
    p_memarea->ma_flgs = 0;
    p_memarea->ma_type = MA_TYPE_INIT;
    p_memarea->ma_maxpages = 0;
    p_memarea->ma_allocpages = 0;
    p_memarea->ma_freepages = 0;
    p_memarea->ma_rsvpages = 0;
    p_memarea->ma_horizline = 0;
    p_memarea->ma_logicstart = 0;
    p_memarea->ma_logicend = 0;
    p_memarea->ma_logicsz = 0;

    memdivmer_t_init(&p_memarea->ma_mdmdata);
    p_memarea->ma_privp = NULL;
}

void memmgrob_init(memmgrob_t * initp) {
    list_t_init(&initp->mo_list);

    initp->mo_lock.lock = 0;
    initp->mo_stus = 0;
    initp->mo_flgs = 0;
    initp->mo_memsz = 0;
    initp->mo_maxpages = 0;
    initp->mo_freepages = 0;
    initp->mo_alocpages = 0;
    initp->mo_resvpages = 0;
    initp->mo_horizline = 0;
    initp->mo_phymem_arr = NULL;
    initp->mo_phymem_nr = 0;
    initp->mo_mpgdesc_arr = NULL;
    initp->mo_mpgdesc_nr= 0;
    initp->mo_memarea_arr = NULL;
    initp->mo_memarea_nr = 0;

    return;
}