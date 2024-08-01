#ifndef VISITOR_H
#define VISITOR_H

struct visitor
{
    void (*visit_function)(struct visitor* v, struct ast_function* node);
    void (*visit_vardecl)(struct visitor* v, struct ast_vardecl* node);
    void (*visit_loop)(struct visitor* v, struct ast_loop* node);
    void (*visit_if)(struct visitor* v, struct ast_if* node);
    void (*visit_break)(struct visitor* v);
    void (*visit_continue)(struct visitor* v);
    void (*visit_assign)(struct visitor* v, struct ast_assign* node);
    void (*visit_return)(struct visitor* v, struct ast_return* node);
    void (*visit_block)(struct visitor* v, struct ast_block* node);
    void (*visit_unary)(struct visitor* v, struct ast_unary* node);
    void (*visit_binary)(struct visitor* v, struct ast_binary* node);
    void (*visit_logical)(struct visitor* v, struct ast_logical* node);
    void (*visit_literal)(struct visitor* v, struct ast_literal* node);
    void (*visit_variable)(struct visitor* v, struct ast_variable* node);
    void (*visit_call)(struct visitor* v, struct ast_call* node);
};

#endif