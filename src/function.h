#ifndef FUNCTION
#define FUNCTION

#include "ast.h"
#include "scope.h"
#include "interpreter.h"
#include "any.h"

struct function
{
    struct ast_function* declaration;
    struct scope* closure;

    int arity;
    any (*callfunc)(struct function* function, struct interpreter* interpreter, struct any_list* arguments);
};

struct function* function_init(struct ast_function* declaration, struct scope* closure);
any callfunc(struct function* function, struct interpreter* interpreter, struct any_list* arguments);
int arity(struct function* function);

#endif