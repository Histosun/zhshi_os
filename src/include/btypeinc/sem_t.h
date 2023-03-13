#ifndef SEM_T_H
#define SEM_T_H

#include "../type.h"
#include "list_t.h"
#include "spinlock.h"

typedef struct atomic {
    volatile sint32_t a_count;
}atomic_t;

typedef struct wlst {
    spinlock_t wl_lock;
    uint_t wl_tdnr;
    list_t wl_list;
} wlst_t;

typedef struct wlst_head {
    list_t wlh_list;
    spinlock_t wlh_lock;
    atomic_t wlh_count;
    void *wlh_privte;
    bool_t (*wlh_upfun)(uint32_t func, struct wlst_head* wlhp);
} wlst_head_t;

#define SEM_FLG_MUTEX 0
#define SEM_FLG_MULTI 1
#define SEM_MUTEX_ONE_LOCK 1
#define SEM_MULTI_LOCK 0

typedef struct s_SEM {
    spinlock_t sem_lock;
    uint_t sem_flg;
    sint_t sem_count;
    wlst_t sem_waitlst;
} sem_t;

#endif