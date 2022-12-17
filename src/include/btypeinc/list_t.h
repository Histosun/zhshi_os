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

KLINE void _list_add(list_t *new_node, list_t *prev_node, list_t *next_node){
    prev_node->next = new_node;
    new_node->next = next_node;
    new_node->prev = prev_node;
    next_node->prev = new_node;
    return;
}

KLINE void list_add(list_t *new_node, list_t *head_node){
    _list_add(new_node, head_node, head_node->next);
    return;
}

#endif