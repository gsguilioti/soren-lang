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
        scope_define(scope, aux->key, aux->value);
        aux = aux->next;
    }
}

void scope_define(struct scope* scope, char* key, any value)
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
            printf("Already defined: %s\n", key);
            exit(1);
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

void scope_assign(struct scope* scope, char* key, any value)
{
    struct scope_node* aux = scope->values->head;

    if(aux != NULL)
    {
        while(aux != NULL)
        {
            if(strcmp(aux->key, key) == 0)
            {
                aux->value = value;
                return;
            }

            aux = aux->next;
        }
    }

    if(scope->parent != NULL)
    {
        scope_assign(scope->parent, key, value);
        return;
    }

    printf("Undefined variable '%s'\n", key);
    exit(1);
}

any scope_get(struct scope* scope, char* key)
{
    struct scope_node* aux = scope->values->head;

    if(aux == NULL)
    {
        printf("Undefined variable '%s'\n", key);
        exit(1);
    }

    if(aux->next == NULL)
    {
        if(strcmp(aux->key, key) == 0)
            return aux->value;
    }

    while(aux != NULL)
    {
        if(strcmp(aux->key, key) == 0)
            return aux->value;

        aux = aux->next;
    }

    printf("Undefined variable '%s'\n", key);
    exit(1);
}