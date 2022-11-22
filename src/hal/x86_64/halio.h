#ifndef HAL_IO_H
#define HAL_IO_H
#include "../../include/type.h"

KLINE uint8_t in_byte(uint16_t port){
    uint8_t ret;
    __asm__ __volatile__("inb %1, %2"
                        :"=a"(ret)
                        :"dN"(port));
    return ret;
}

KLINE uint16_t in_word(uint16_t port){
    uint16_t ret;
    __asm__ __volatile__("inw %1, %2"
            :
            :"dN"(port), "a"(ret));
    return ret;

}

KLINE void out_byte(uint16_t port, uint8_t val){
    __asm__ __volatile__("outb %1, %2"
            :
            :"dN"(port), "a"(ret));
}

KLINE void out_word(uint16_t port, uint16_t val){

}

#endif