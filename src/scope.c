#include <string.h>
#include <stdio.h>
#include "scope.h"

struct scope* scope_init()
{
    struct scope* scope = (struct scope*)malloc(sizeof(struct scope));
    struct scope_list* list = scope_list_init();
    scope->values = list;
    scope->parent = NULL;
    return scope;
}

struct scope_list* scope_list_init()
{
    struct scope_list* list = (struct scope_list*)malloc(sizeof(struct scope_list));
    list->size = 0;
    list->head = NULL;
    return list;
}

void scope_copy(struct scope* parent, struct scope* scope)
{
    if(parent == NULL)
        return;

    scope->parent = parent;

    if(parent->values->head == NULL)
        return;

    struct scope_node* aux = parent->values->head;
    while(aux != NULL)
    {
        scope_set(scope, aux->key, aux->value);
        aux = aux->next;
    }
}

void scope_set(struct scope* scope, char* key, any value)
{
    struct scope_node* aux = scope->values->head;

    if(aux == NULL)
    {
        struct scope_node* new = (struct scope_node*)malloc(sizeof( struct scope_node));
        new->next = NULL;
        new->key = key;
        new->value = value;
        scope->values->head = new;
        scope->values->size += 1;
        return;
    }

    while(aux->next != NULL)
    {
        if(strcmp(aux->key, key) == 0)
        {
            aux->value = value;
            return;
        }

        aux = aux->next;
    }

    struct scope_node* new = (struct scope_node*)malloc(sizeof( struct scope_node));
    new->next = NULL;
    new->key = key;
    new->value = value;

    aux->next = new;
    scope->values->size += 1;
}

any scope_get(struct scope* scope, char* key)
{
    struct scope_node* aux = scope->values->head;

    while(aux->next != NULL)
    {
        if(strcmp(aux->key, key) == 0)
            return aux->value;

        aux = aux->next;
    }

    any empty = { .type = VOID};
    return empty;
}