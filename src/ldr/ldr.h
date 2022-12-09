#ifndef IDR_H
#define IDR_H

#include "ldrtype.h"

#define IKSTACK_PHYADR 0x9f000
#define IKSTACK_SIZE 0x1000

kernel_desc_t* kd;

void init_mach_param();

void die();

#endif