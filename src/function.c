#include "function.h"
#include "interpreter.h"

struct function* function_init(struct ast_function* declaration, struct scope* closure)
{
    struct function* new = (struct function*)malloc(sizeof(struct function));
    new->declaration = declaration;
    new->closure = closure;
    new->call = call;
}

any call(struct function* function, struct interpreter* interpreter, struct any_list* arguments)
{
    struct scope* environment = scope_init();
    scope_copy(function->closure, environment);

    for (int i = 0; i < function->declaration->params->size; ++i)
        scope_assign(environment, ast_list_at(function->declaration->params, i)->variable->name.lexeme, any_list_at(arguments, i));
    
    execute_block(interpreter, function->declaration->body);
    //capturar o retorno
    //retornar o retorno
}

int arity(struct function* function)
{
    return function->declaration->params->size;
}