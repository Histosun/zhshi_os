#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "../type.h"

typedef struct
{
    volatile uint32_t lock;
} spinlock_t;

#endif