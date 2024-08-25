#include <stdlib.h>

#include "any.h"

struct any_list* any_list_init()
{
    struct any_list* new = (struct any_list*)malloc(sizeof(struct any_list));
    new->size = 0;
    new->head = NULL;
    return new;
}

void any_list_add(struct any_list* list, any value)
{
    struct any_node* new = (struct any_node*)malloc(sizeof(struct any_node));
    new->next = NULL;
    new->value = value;

    if(list->head == NULL)
    {
        list->head = new;
        list->size += 1;
        return;
    }

    struct any_node* aux = list->head;
    while(aux->next != NULL)
        aux = aux->next;

    aux->next = new;
    list->size += 1;
    return;
}

any any_list_at(struct any_list* list, int index)
{
    any empty = {.type = VOID};
    if(list->head == NULL)
        return empty;

    if(index == 0)
        return list->head->value;
    
    struct any_node* aux = list->head;
    int i = 0;
    while(i < index)
    {
        aux = aux->next;
        i += 1;
    }

    return aux->value;
}
