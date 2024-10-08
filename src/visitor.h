#ifndef VISITOR_H
#define VISITOR_H

#include "any.h"

struct visitor
{
    any (*visit_function)(struct interpreter* i, struct ast_function* node);
    any (*visit_vardecl)(struct interpreter* i, struct ast_vardecl* node);
    any (*visit_loop)(struct interpreter* i, struct ast_loop* node);
    any (*visit_if)(struct interpreter* i, struct ast_if* node);
    any (*visit_break)(struct interpreter* i);
    any (*visit_continue)(struct interpreter* i);
    any (*visit_assign)(struct interpreter* i, struct ast_assign* node);
    any (*visit_return)(struct interpreter* i, struct ast_return* node);
    any (*visit_block)(struct interpreter* i, struct ast_block* node);
    any (*visit_unary)(struct interpreter* i, struct ast_unary* node);
    any (*visit_binary)(struct interpreter* i, struct ast_binary* node);
    any (*visit_logical)(struct interpreter* i, struct ast_logical* node);
    any (*visit_literal)(struct interpreter* i, struct ast_literal* node);
    any (*visit_variable)(struct interpreter* i, struct ast_variable* node);
    any (*visit_call)(struct interpreter* i, struct ast_call* node);
};

#endif