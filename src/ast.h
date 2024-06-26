#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include "token.h"

enum ast_type
{
    VARDECL, FUNDECL,
    ASSIGN, BLOCK, IF, LOOP,
    RETURN, BREAK, CONTINUE,
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
        struct ast_block* block;
        struct ast_if* _if;
        struct ast_loop* loop;
        struct ast_function* function;
        struct ast_return* _return;
    };
};

struct ast_function
{
    struct token name;
    struct token_list* params;
    struct ast_list* body;
};

struct ast_vardecl
{
    struct token name;
    struct ast_node* initializer;
};

struct ast_loop
{
    struct ast_node* condition;
    struct ast_node* body;
};

struct ast_if
{
    struct ast_node* condition;
    struct ast_node* then;
    struct ast_node* _else;
};

struct ast_assign
{
    struct token name;
    struct ast_node* value;
};

struct ast_return
{
    struct token name;
    struct ast_node* value;
};

struct ast_block
{
    struct ast_list* statements;
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

enum literal_type { INT, BOOL };
struct ast_literal
{
    enum literal_type literal_type;
    struct token value;
};

struct ast_variable
{
    struct token name;
};

struct ast_node* ast_function(struct token name, struct token_list* params, struct ast_list* body);
struct ast_node* ast_vardecl(struct token name, struct ast_node* initializer);
struct ast_node* ast_loop(struct ast_node* condition, struct ast_node* body);
struct ast_node* ast_if(struct ast_node* condition, struct ast_node* then, struct ast_node* _else);
struct ast_node* ast_break();
struct ast_node* ast_continue();
struct ast_node* ast_assign(struct token name, struct ast_node* value);
struct ast_node* ast_return(struct token name, struct ast_node* value);
struct ast_node* ast_block(struct ast_list* statements);
struct ast_node* ast_unary(struct token op, struct ast_node* right);
struct ast_node* ast_binary(struct token op, struct ast_node* left, struct ast_node* right);
struct ast_node* ast_logical(struct token op, struct ast_node* left, struct ast_node* right);
struct ast_node* ast_unary(struct token op, struct ast_node* right);
struct ast_node* ast_literal(int literal_type, struct token value);
struct ast_node* ast_variable(struct token value);

/* 
* ===================
* ast list definition
* ===================
*/
struct ast_list_node
{
    struct ast_node* value;
    struct ast_list_node* next;
};

struct ast_list
{
    struct ast_list_node* head;
    size_t size;
};

struct ast_list* ast_list_init();
void ast_list_add(struct ast_list* list, struct ast_node* token);

#endif