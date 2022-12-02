#ifndef LIST_T_H
#define LIST_T_H

#include "../type.h"

typedef struct list
{
    struct list * prev, * next;
} list_t;

KLINE void list_t_init(list_t *list)
{
    list->prev = list;
    list->next = list;
    return;
}

#endif