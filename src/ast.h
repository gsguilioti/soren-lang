#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include "token.h"

enum ast_type
{
    NUMBER, BINARY
};

struct ast_node
{
    enum ast_type type;
    union
    {
        struct ast_binary* binary;
        struct ast_primary* primary;
    };
};

struct ast_binary
{
    struct token op;
    struct ast_node* left;
    struct ast_node* right;     
};

struct ast_primary
{
    struct token value;
};

struct ast_node* ast_binary(int type, struct token op, struct ast_node* left, struct ast_node* right);
struct ast_node* ast_primary(int type, struct token value);

#endif