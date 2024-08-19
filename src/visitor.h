#ifndef VISITOR_H
#define VISITOR_H

#include "any.h"

struct visitor
{
    any (*visit_function)(struct visitor* v, struct ast_function* node);
    any (*visit_vardecl)(struct visitor* v, struct ast_vardecl* node);
    any (*visit_loop)(struct visitor* v, struct ast_loop* node);
    any (*visit_if)(struct visitor* v, struct ast_if* node);
    any (*visit_break)(struct visitor* v);
    any (*visit_continue)(struct visitor* v);
    any (*visit_assign)(struct visitor* v, struct ast_assign* node);
    any (*visit_return)(struct visitor* v, struct ast_return* node);
    any (*visit_block)(struct visitor* v, struct ast_block* node);
    any (*visit_unary)(struct visitor* v, struct ast_unary* node);
    any (*visit_binary)(struct visitor* v, struct ast_binary* node);
    any (*visit_logical)(struct visitor* v, struct ast_logical* node);
    any (*visit_literal)(struct visitor* v, struct ast_literal* node);
    any (*visit_variable)(struct visitor* v, struct ast_variable* node);
    any (*visit_call)(struct visitor* v, struct ast_call* node);
};

#endif