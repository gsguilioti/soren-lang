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
    };
} any;

#endif