#ifndef HAL_MM_H
#define HAL_MM_H

#include "../../include/type.h"
#include "../../lib/spinlock.h"
#include "haltype.h"

#define PHYMMAP_MAX 200

phy_memory_t phym_map[PHYMMAP_MAX];

void init_phymm();

#endif