#include "interpreter.h"
#include "visitor.h"
#include "enums.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct interpreter* interpreter_init()
{
    struct interpreter* interpreter = malloc(sizeof(struct interpreter));
    struct visitor* visitor = malloc(sizeof(struct visitor));

    struct scope* global = scope_init();
    interpreter->environment = global;

    interpreter->v = visitor;

    interpreter->v->visit_function = visit_function;
    interpreter->v->visit_vardecl = visit_vardecl;
    interpreter->v->visit_loop = visit_loop;
    interpreter->v->visit_if = visit_if;
    interpreter->v->visit_break = visit_break;
    interpreter->v->visit_continue = visit_continue;
    interpreter->v->visit_assign = visit_assign;
    interpreter->v->visit_return = visit_return;
    interpreter->v->visit_block = visit_block;
    interpreter->v->visit_unary = visit_unary;
    interpreter->v->visit_binary = visit_binary;
    interpreter->v->visit_logical = visit_logical;
    interpreter->v->visit_literal = visit_literal;
    interpreter->v->visit_variable = visit_variable;
    interpreter->v->visit_call = visit_call;

    return interpreter;
}

void interpret(struct interpreter* interpreter, struct ast_list* statements)
{
    for(int i = 0; i < statements->size; ++i)
        evaluate(interpreter, ast_list_at(statements, i));
}

void execute(struct interpreter* interpreter, struct ast_node* node)
{
    if(!node) return;

    switch(node->type)
    {
        case VARDECL:   interpreter->v->visit_vardecl(interpreter, node->vardecl);    break;
        case FUNDECL:   interpreter->v->visit_function(interpreter, node->function);  break;
        case ASSIGN:    interpreter->v->visit_assign(interpreter, node->assign);      break;
        case BLOCK:     interpreter->v->visit_block(interpreter, node->block);        break;
        case IF:        interpreter->v->visit_if(interpreter, node->_if);             break;
        case LOOP:      interpreter->v->visit_loop(interpreter, node->loop);          break;
        case RETURN:    interpreter->v->visit_return(interpreter, node->_return);     break;
        case BREAK:     interpreter->v->visit_break(interpreter);                     break;
        case CONTINUE:  interpreter->v->visit_continue(interpreter);                  break;
        case BINARY:    interpreter->v->visit_binary(interpreter, node->binary);      break;
        case LOGICAL:   interpreter->v->visit_logical(interpreter, node->logical);    break;
        case UNARY:     interpreter->v->visit_unary(interpreter, node->unary);        break;
        case LITERAL:   interpreter->v->visit_literal(interpreter, node->literal);    break;
        case VARIABLE:  interpreter->v->visit_variable(interpreter, node->variable);  break;
        case CALL:      interpreter->v->visit_call(interpreter, node->call);          break;
        default:
            exit(1);
    }
}

any evaluate(struct interpreter* interpreter, struct ast_node* node)
{
    if(!node) return;

    switch(node->type)
    {
        case VARDECL:   return interpreter->v->visit_vardecl(interpreter, node->vardecl);    break;
        case FUNDECL:   return interpreter->v->visit_function(interpreter, node->function);  break;
        case ASSIGN:    return interpreter->v->visit_assign(interpreter, node->assign);      break;
        case BLOCK:     return interpreter->v->visit_block(interpreter, node->block);        break;
        case IF:        return interpreter->v->visit_if(interpreter, node->_if);             break;
        case LOOP:      return interpreter->v->visit_loop(interpreter, node->loop);          break;
        case RETURN:    return interpreter->v->visit_return(interpreter, node->_return);     break;
        case BREAK:     return interpreter->v->visit_break(interpreter);                     break;
        case CONTINUE:  return interpreter->v->visit_continue(interpreter);                  break;
        case BINARY:    return interpreter->v->visit_binary(interpreter, node->binary);      break;
        case LOGICAL:   return interpreter->v->visit_logical(interpreter, node->logical);    break;
        case UNARY:     return interpreter->v->visit_unary(interpreter, node->unary);        break;
        case LITERAL:   return interpreter->v->visit_literal(interpreter, node->literal);    break;
        case VARIABLE:  return interpreter->v->visit_variable(interpreter, node->variable);  break;
        case CALL:      return interpreter->v->visit_call(interpreter, node->call);          break;
        default:
            exit(1);
    }
}

static int is_truthy(any object)
{
    if(object.type == VOID) return 0;
    if(object.type == BOOL) return object.bool;

    return 1;
}

static int is_equal(any first, any second)
{
    if(first.type == NUM)
    {
        if(second.type != NUM)
            return 0;
        
        return first.num == second.num;
    }
    else if(first.type == BOOL)
    {
        if(second.type != BOOL)
            return 0;

        return first.bool == second.bool;
    }
    else if(first.type == STRING)
    {
        if(second.type != STRING)
            return 0;

        return !strcmp(first.string, second.string);
    }

    return 0;
}

static void validate_unary(any operand)
{
    if(operand.type == NUM) return;

    printf("Operand must be a number.\n");
    exit(1);
}

static void validate_binary(any left, any right)
{
    if(left.type == NUM && right.type == NUM) return;

    printf("Operands must be a number.\n");
    exit(1);
}

static any solve_binary(enum token_type op, any left, any right)
{
    any value;
    value.type = VOID;

    switch(op)
    {
        case TOKEN_GREAT:
            value.type = BOOL;
            value.bool = left.num > right.num;
            break;
        case TOKEN_LESS:
            value.type = BOOL;
            value.bool = left.num < right.num;
            break;
        case TOKEN_GTHEN:
            value.type = BOOL;
            value.bool = left.num >= right.num;
            break;
        case TOKEN_LTHEN:
            value.type = BOOL;
            value.bool = left.num <= right.num;
            break;
        case TOKEN_EQUAL:
            value.type = BOOL;
            value.bool = is_equal(left, right);
            break;
        case TOKEN_NOTEQUAL:
            value.type = BOOL;
            value.bool = !is_equal(left, right);
            break;
        case TOKEN_PLUS:
            value.type = NUM;
            value.num = left.num + right.num;
            break;
        case TOKEN_MINUS:
            value.type = NUM;
            value.num = left.num - right.num;
            break;
        case TOKEN_MULT:
            value.type = NUM;
            value.num = left.num * right.num;
            break;
        case TOKEN_DIV:
            value.type = NUM;
            value.num = left.num / right.num;
            break;
        case TOKEN_MOD:
            value.type = NUM;
            value.num = (int)left.num % (int)right.num;
            break;
    }

    return value;
}

static any solve_unary(enum token_type op, any right)
{
    any value;
    value.type = VOID;

    switch(op)
    {
        case TOKEN_NOT:
            value.type = BOOL;
            value.bool = !is_truthy(right);
            break;
        case TOKEN_MINUS:
            value.type = NUM;
            value.num = -right.num;
            break;
    }

    return value;
}

any visit_function(struct interpreter* i, struct ast_function* node)
{
    printf("visit_function\n");
}

any visit_vardecl(struct interpreter* i, struct ast_vardecl* node)
{
    any value;
    if(node->initializer != NULL)
        value = evaluate(i, node->initializer);

    scope_set(i->environment, node->var->variable->name.lexeme, value);
    
    any empty = { .type = VOID};
    return empty;
}

any visit_loop(struct interpreter* i, struct ast_loop* node)
{
    while(is_truthy(evaluate(i, node->condition)))
        execute(i, node->body);

    any value = { .type = VOID};
    return value;
}

any visit_if(struct interpreter* i, struct ast_if* node)
{
    if(is_truthy(evaluate(i, node->condition)))
        execute(i, node->then);
    else if(node->_else != NULL)
        execute(i, node->_else);

    any value = { .type = VOID};
    return value;
}

any visit_break(struct interpreter* i)
{
    printf("visit_break\n");
}

any visit_continue(struct interpreter* i)
{
    printf("visit_continue\n");
}

any visit_assign(struct interpreter* i, struct ast_assign* node)
{
    any value = evaluate(i, node->value);
    scope_set(i->environment, node->name.lexeme, value);

    return value;
}

any visit_return(struct interpreter* i, struct ast_return* node)
{
    printf("visit_return\n");
}

any visit_block(struct interpreter* i, struct ast_block* node)
{
    struct scope* prev = i->environment;
    struct scope* env = scope_init();
    scope_copy(prev, env);
    i->environment = env;

    for(int j = 0; j < node->statements->size; ++j)
    {
        execute(i, ast_list_at(node->statements, j));
    }
    
    i->environment = prev;
    free(env);
}

any visit_unary(struct interpreter* i, struct ast_unary* node)
{
    any right = evaluate(i, node->right);

    validate_unary(right);
    return solve_unary(node->op.type, right);
}

any visit_binary(struct interpreter* i, struct ast_binary* node)
{
    any left = evaluate(i, node->left);
    any right = evaluate(i, node->right);

    validate_binary(left, right);
    return solve_binary(node->op.type, left, right);
}

any visit_logical(struct interpreter* i, struct ast_logical* node)
{
    any left = evaluate(i, node->left);

    if(node->op.type == TOKEN_OR)
        if(is_truthy(left)) return left;
    else
        if(!is_truthy(left)) return left;

    return evaluate(i, node->right);
}

any visit_literal(struct interpreter* i, struct ast_literal* node)
{
    return node->value;
}

any visit_variable(struct interpreter* i, struct ast_variable* node)
{
    return scope_get(i->environment, node->name.lexeme);
}

any visit_call(struct interpreter* i, struct ast_call* node)
{
    printf("visit_call\n");
}
