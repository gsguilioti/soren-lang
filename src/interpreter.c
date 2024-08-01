#include "interpreter.h"
#include "visitor.h"

#include <stdlib.h>

struct interpreter* interpreter_init()
{
    struct interpreter* interpreter = malloc(sizeof(struct interpreter));
    struct visitor* visitor = malloc(sizeof(struct visitor));

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
}

void interpret(struct interpreter* interpreter, struct ast_node* node)
{
    if(!node) return;

    switch(node->type)
    {
        case VARDECL:   interpreter->v->visit_vardecl(interpreter->v, node->vardecl);    break;
        case FUNDECL:   interpreter->v->visit_function(interpreter->v, node->function);    break;
        case ASSIGN:    interpreter->v->visit_assign(interpreter->v, node->assign);      break;
        case BLOCK:     interpreter->v->visit_block(interpreter->v, node->block);        break;
        case IF:        interpreter->v->visit_if(interpreter->v, node->_if);             break;
        case LOOP:      interpreter->v->visit_loop(interpreter->v, node->loop);          break;
        case RETURN:    interpreter->v->visit_return(interpreter->v, node->_return);      break;
        case BREAK:     interpreter->v->visit_break(interpreter->v);                     break;
        case CONTINUE:  interpreter->v->visit_continue(interpreter->v);                  break;
        case BINARY:    interpreter->v->visit_binary(interpreter->v, node->binary);      break;
        case LOGICAL:   interpreter->v->visit_logical(interpreter->v, node->logical);    break;
        case UNARY:     interpreter->v->visit_unary(interpreter->v, node->unary);        break;
        case LITERAL:   interpreter->v->visit_literal(interpreter->v, node->literal);    break;
        case VARIABLE:  interpreter->v->visit_variable(interpreter->v, node->variable);  break;
        case CALL:      interpreter->v->visit_call(interpreter->v, node->call);          break;
        default:
            exit(1);
    }
}

void visit_function(struct visitor* v, struct ast_function* node)
{

}

void visit_vardecl(struct visitor* v, struct ast_vardecl* node)
{

}

void visit_loop(struct visitor* v, struct ast_loop* node)
{

}

void visit_if(struct visitor* v, struct ast_if* node)
{

}

void visit_break(struct visitor* v)
{

}

void visit_continue(struct visitor* v)
{

}

void visit_assign(struct visitor* v, struct ast_assign* node)
{

}

void visit_return(struct visitor* v, struct ast_return* node)
{

}

void visit_block(struct visitor* v, struct ast_block* node)
{

}

void visit_unary(struct visitor* v, struct ast_unary* node)
{

}

void visit_binary(struct visitor* v, struct ast_binary* node)
{

}

void visit_logical(struct visitor* v, struct ast_logical* node)
{

}

void visit_literal(struct visitor* v, struct ast_literal* node)
{

}

void visit_variable(struct visitor* v, struct ast_variable* node)
{

}

void visit_call(struct visitor* v, struct ast_call* node)
{

}
