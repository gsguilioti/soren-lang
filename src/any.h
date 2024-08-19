#ifndef ANY
#define ANY

#include "ast.h"

typedef struct any
{
    enum type type;
    union {
        char* string;
        float num;
        int bool;
    };
} any;

#endif