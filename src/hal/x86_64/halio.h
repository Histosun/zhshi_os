#ifndef HAL_IO_H
#define HAL_IO_H
#include "../../include/type.h"

KLINE uint8_t in_byte(const uint16_t port){
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0"
            :"=a"(ret)
            :"dN"(port));
    return ret;
}

KLINE uint16_t in_word(const uint16_t port){
    uint16_t ret;
    __asm__ __volatile__("inw %1, %0"
            :"=a"(ret)
            :"dN"(port));
    return ret;

}

KLINE void out_byte(uint16_t port, uint8_t val){
    __asm__ __volatile__("outb %0, %1"
            :
            : "a"(val), "dN" (port));
}

KLINE void out_word(uint16_t port, uint16_t val){
    __asm__ __volatile__("outw %0, %1"
            :
            : "a"(val), "dN"(port));
}

#endif