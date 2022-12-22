#ifndef HAL_MM_T_H
#define HAL_MM_T_H

#include "../../../include/type.h"
#include "../../../include/btypeinc/spinlock.h"
#include "../../../include/btypeinc/list_t.h"
#include "../../../include/btypeinc/sem_t.h"
#include "halmm.h"

//memory page management struct

#define MPAD_PAGE_MAX (8)

#define MF_OLKTY_INIT (0)
#define MF_OLKTY_ODER (1)
#define MF_OLKTY_BAFH (2)
#define MF_OLKTY_TOBJ (3)

#define MF_LSTTY_LIST (0)
#define MF_MOCTY_FREE (0)
#define MF_MOCTY_KRNL (1)
#define MF_MOCTY_USER (2)
#define MF_MRV1_VAL (0)
#define MF_UINDX_INIT (0)
#define MF_UINDX_MAX (0xffffff)
#define MF_MARTY_INIT (0)
#define MF_MARTY_HWD (1)
#define MF_MARTY_KRL (2)
#define MF_MARTY_PRC (3)
#define MF_MARTY_SHD (4)

//memory page flags
typedef struct mpgflgs{
    uint32_t mf_olkty:2;    //
    uint32_t mf_lstty:1;
    uint32_t mf_mocty:2;
    uint32_t mf_marty:3;
    uint32_t mf_uindx:24;
}__attribute__((packed)) mpgflgs_t;

//physical address flags
#define  PAF_NO_ALLOC (0)
#define  PAF_ALLOC (1)
#define  PAF_NO_SHARED (0)
#define  PAF_NO_SWAP (0)
#define  PAF_NO_CACHE (0)
#define  PAF_NO_KMAP (0)
#define  PAF_NO_LOCK (0)
#define  PAF_NO_DIRTY (0)
#define  PAF_NO_BUSY (0)
#define  PAF_RSV_VAL (0)
#define  PAF_INIT_PADRS (0)

typedef struct phyadrflgs{
    uint64_t paf_alloc:1;
    uint64_t paf_shared:1;
    uint64_t paf_swap:1;
    uint64_t paf_cache:1;
    uint64_t paf_kmap:1;
    uint64_t paf_loc:1;
    uint64_t paf_dirty:1;
    uint64_t paf_busy:1;
    uint64_t paf_rsv:4;
    uint64_t paf_phyadr:52;
}__attribute__((packed)) phyadrflgs_t;

//memory page descriptor
typedef struct mpgdesc{
    list_t mp_list;
    spinlock_t mp_lock;
    mpgflgs_t mp_flgs;
    phyadrflgs_t mp_phyadr;
    void * mp_odlink;
}__attribute__((packed)) mpgdesc_t;

void mpgdesc_t_init(mpgdesc_t * mpgdesc);

// memory page alloc free head list
#define BAFH_STUS_INIT 0
#define BAFH_STUS_ONEM 1
#define BAFH_STUS_DIVP 2
#define BAFH_STUS_DIVM 3

typedef struct mpafhlst {
    spinlock_t af_lock;
    uint32_t af_stus;
    uint_t af_oder;
    uint_t af_oderpnr;
    uint_t af_fobjnr;
    uint_t al_mobjnr;
    uint_t af_alcindx;
    uint_t af_freindx;
    list_t af_frelst;
    list_t af_alclst;
} mpafhlst_t;

#define MDIVMER_ARR_LMAX 52
typedef struct memdivmer
{
    spinlock_t dm_lock;
    uint32_t dm_stus;
    uint_t dm_divnr;
    uint_t dm_mernr;
    mpafhlst_t dm_mdmlielst[MDIVMER_ARR_LMAX];
    mpafhlst_t dm_onemsalst;
}memdivmer_t;

#define MA_TYPE_INIT 0
#define MA_TYPE_HWAD 1
#define MA_TYPE_KRNL 2
#define MA_TYPE_PROC 3
#define MEMAREA_MAX 3
#define MA_HWAD_LSTART 0
#define MA_HWAD_LSZ 0x2000000
#define MA_HWAD_LEND (MA_HWAD_LSTART+MA_HWAD_LSZ-1)
#define MA_KRNL_LSTART 0x2000000
#define MA_KRNL_LSZ (0x40000000-0x2000000)
#define MA_KRNL_LEND (MA_KRNL_LSTART+MA_KRNL_LSZ-1)
#define MA_PROC_LSTART 0x40000000
#define MA_PROC_LSZ (0xffffffff-0x40000000)
#define MA_PROC_LEND (MA_PROC_LSTART+MA_PROC_LSZ)

struct memarea;

typedef struct mafuncobjs {
    uint64_t (*mafo_init)(struct memarea * memarea, void* valp, uint_t val);
    uint64_t (*mafo_exit)(struct memarea * memarea);
    uint64_t (*mafo_aloc)(struct memarea * memarea, void * mafrspack, void * valp, uint_t val);
    uint64_t (*mafo_free)(struct memarea * memarea, void * mafrspack, void * valp, uint_t val);
    uint64_t (*mafo_recy)(struct memarea * memarea, void * mafrspack, void * valp, uint_t val);
}mafuncobjs_t;

typedef struct memarea{
    list_t ma_list;
    spinlock_t ma_lock;
    uint_t ma_stus;
    uint_t ma_flgs;
    uint_t ma_type;
    sem_t ma_sem;
    wlst_head_t ma_waitlst;
    uint_t ma_maxpages;
    uint_t ma_allocpages;
    uint_t ma_freepages;
    uint_t ma_rsvpages;
    uint_t ma_horizline;
    adr_t ma_logicstart;
    adr_t ma_logicend;
    uint_t ma_logicsz;
    struct mafuncobjs ma_funcobj;
    memdivmer_t ma_mdmdata;
    void * ma_privp;
} memarea_t;

void memarea_t_init(memarea_t * p_memarea);

typedef struct s_MEMMGROB {
    list_t mo_list;
    spinlock_t mo_lock;
    uint_t mo_stus;
    uint_t mo_flgs;
    uint64_t mo_memsz;
    uint64_t mo_maxpages;
    uint64_t mo_freepages;
    uint64_t mo_alocpages;
    uint64_t mo_resvpages;
    uint64_t mo_horizline;
    phymmap_t * mo_phymem_arr;
    uint64_t mo_phymem_nr;
    mpgdesc_t * mo_mpgdesc_arr;
    uint64_t mo_mpgdesc_nr;
    memarea_t * mo_memarea_arr;
    uint64_t mo_memarea_nr;
}memmgrob_t;

void memmgrob_init(memmgrob_t * initp);

#endif