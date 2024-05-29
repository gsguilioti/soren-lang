#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include "token.h"

enum ast_type
{
    ASSIGN, VARDECL,
    BINARY, LOGICAL, UNARY,
    LITERAL, VARIABLE
};

struct ast_node
{
    enum ast_type type;
    union
    {
        struct ast_binary* binary;
        struct ast_logical* logical;
        struct ast_unary* unary;
        struct ast_literal* literal;
        struct ast_variable* variable;
        struct ast_assign* assign;
        struct ast_vardecl* vardecl;
    };
};

struct ast_vardecl
{
    struct token name;
    struct ast_node* initializer;
};

struct ast_assign
{
    struct token name;
    struct ast_node* value;
};


struct ast_binary
{
    struct token op;
    struct ast_node* left;
    struct ast_node* right;     
};

struct ast_logical
{
    struct token op;
    struct ast_node* left;
    struct ast_node* right;     
};

struct ast_unary
{
    struct token op;
    struct ast_node* right;
};

enum literal_type { INT, BOOL};
struct ast_literal
{
    enum literal_type literal_type;
    struct token value;
};

struct ast_variable
{
    struct token name;
};

struct ast_node* ast_vardecl(struct token name, struct ast_node* initializer);
struct ast_node* ast_assign(struct token name, struct ast_node* value);
struct ast_node* ast_unary(struct token op, struct ast_node* right);
struct ast_node* ast_binary(struct token op, struct ast_node* left, struct ast_node* right);
struct ast_node* ast_logical(struct token op, struct ast_node* left, struct ast_node* right);
struct ast_node* ast_unary(struct token op, struct ast_node* right);
struct ast_node* ast_literal(int literal_type, struct token value);
struct ast_node* ast_variable(struct token value);

#endif