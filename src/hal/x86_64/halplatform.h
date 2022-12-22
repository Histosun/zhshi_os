#ifndef HALPLATFORM_H
#define HALPLATFORM_H

#include "../../include/type.h"

#define KRNL_MAP_VIRTADDRESS_SIZE 0x400000000
#define KRNL_VIRTUAL_ADDRESS_START 0xffff800000000000
#define KRNL_VIRTUAL_ADDRESS_END 0xffffffffffffffff
#define USER_VIRTUAL_ADDRESS_START 0
#define USER_VIRTUAL_ADDRESS_END 0x00007fffffffffff
#define KRNL_MAP_PHYADDRESS_START 0
#define KRNL_MAP_PHYADDRESS_END 0x400000000
#define KRNL_MAP_PHYADDRESS_SIZE 0x400000000
#define KRNL_MAP_VIRTADDRESS_START KRNL_VIRTUAL_ADDRESS_START
#define KRNL_MAP_VIRTADDRESS_END (KRNL_MAP_VIRTADDRESS_START+KRNL_MAP_VIRTADDRESS_SIZE)
#define KRNL_ADDR_ERROR 0xf800000000000

static inline adr_t viradr_to_phyadr(adr_t kviradr) {
    if(kviradr < KRNL_VIRTUAL_ADDRESS_START || kviradr > KRNL_VIRTUAL_ADDRESS_END)
        while (1);
    return kviradr - KRNL_VIRTUAL_ADDRESS_START;
}

static inline adr_t phyadr_to_viradr(adr_t kphyadr) {
    if(kphyadr >= KRNL_MAP_PHYADDRESS_END)
        while (1);
    return kphyadr + KRNL_VIRTUAL_ADDRESS_START;
}

#endif