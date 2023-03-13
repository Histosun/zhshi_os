#ifndef MEM_H
#define MEM_H

#include "type.h"

KLINE void memset(void * addr, char val, uint32_t size) {
    char * src = addr;
    for(uint32_t i = 0; i<size; ++i){
        src[i] = val;
    }
}

KLINE void memcpy(void * s, void * d, uint32_t size) {
    char * src = s, * dest = d;
    for(uint32_t i = 0; i<size; ++i){
        dest[i] = src[i];
    }
}

#endif