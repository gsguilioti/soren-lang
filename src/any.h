#ifndef ANY
#define ANY

#include "enums.h"

typedef struct any
{
    enum type type;
    union {
        char* string;
        float num;
        int bool;
        struct function* function;
    };
} any;

struct any_list
{
    struct any_node* head;
    int size;
};

struct any_node
{
    struct any_node* next;
    any value;
};

struct any_list* any_list_init();
void any_list_add(struct any_list* list, any value);
any any_list_at(struct any_list* list, int index);

#endif