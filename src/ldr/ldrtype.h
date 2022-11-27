#ifndef LDRTYPE_H
#define LDRTYPE_H
#include "../include/type.h"

#define KERNEL_START 0x200000
#define E820_DESC 0x5000
#define E820_MAX 200
#define ZHOS_MAGIC (uint64_t)((((uint64_t)'Z')<<56)|(((uint64_t)'H')<<48)|(((uint64_t)'O')<<40)|(((uint64_t)'S')<<32)|(((uint64_t)'M')<<24)|(((uint64_t)'A')<<16)|(((uint64_t)'C')<<8)|((uint64_t)'H'))

typedef struct krlmach_info
{
    uint64_t zhos_magic;    //magic of zhos
    uint64_t init_stack;    //kernel stack address
    uint64_t stack_sz;      //kernel stack size
    uint64_t cpu_mode;      //cpu mode
    uint64_t mach_memsize;    //memory size of machine
    uint64_t e820_adr;      //address of e820 array
    uint64_t e820_nr;       //number of e820 entry
    uint64_t e820_sz;       //size of e820 array
}__attribute__((packed)) krlmach_info_t;

typedef struct kernel_desc{
    uint64_t kernel_magic;
    uint64_t kernel_start;
    uint64_t offset;
    uint64_t kernel_size;
    uint64_t next_pg;
}__attribute__((packed)) kernel_desc_t;

#define MIPADR ((krlmach_info_t*)(0x100000))

#define E820_DESC_ADDR 0x5000
#define E820_ADDR E820_DESC_ADDR + sizeof(uint32_t)
#define E820_MAX 200
#define RAM_USABLE 1

typedef struct e820_map {
    uint64_t addr;
    uint64_t size;
    uint32_t type;
}__attribute__((packed)) e820_map_t;

typedef struct e820_desc {
    uint32_t e820_num;
    e820_map_t maps[E820_MAX];
}__attribute__((packed)) e820_desc_t;

#endif