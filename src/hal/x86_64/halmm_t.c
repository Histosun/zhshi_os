#include "halmm_t.h"

void mpdesc_t_init(mpgdesc_t * mpgdesc){
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