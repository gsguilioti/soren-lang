#ifndef FUNCTION
#define FUNCTION

#include "ast.h"
#include "scope.h"

struct function
{
    struct ast_function* declaration;
    struct scope* closure;

    int arity;
    any (*call)(struct interpreter* interpreter, struct any_list* arguments);
};

struct function* function_init(struct ast_function* declaration, struct scope* closure);
any call(struct function* function, struct interpreter* interpreter, struct any_list* arguments);
int arity(struct function* function);

#endif