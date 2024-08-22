#ifndef SCOPE
#define SCOPE

#include <stdlib.h>
#include "any.h"

struct scope
{
    struct scope_list* values;
    struct scope* parent;
};

struct scope_list
{
    int size;
    struct scope_node* head;
};

struct scope_node
{
    struct scope_node* next;
    char* key;
    any value;
};

struct scope* scope_init();
struct scope_list* scope_list_init();
void scope_copy(struct scope* parent, struct scope* scope);
void scope_define(struct scope* scope, char* key, any value);
void scope_assign(struct scope* scope, char* key, any value);
any scope_get(struct scope* scope, char* key);

#endif