#include "../include/mem.h"

void memset(void * addr, char val, uint32_t size){
    char * src = addr;
    for(uint32_t i = 0; i<size; ++i){
        src[i] = val;
    }
}