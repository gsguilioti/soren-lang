#include "ast.h"

static struct ast_node* ast_node()
{
    struct ast_node* new = (struct ast_node*)malloc(sizeof(struct ast_node));
    if(new == NULL)
        return NULL;

    return new;
}

struct ast_node* ast_vardecl(struct token name, struct ast_node* initializer)
{
    struct ast_node* node = ast_node();
    node->type = VARDECL;
    node->vardecl = (struct ast_vardecl*)malloc(sizeof(struct ast_vardecl));
    node->vardecl->name = name;
    node->vardecl->initializer = initializer;
    return node;
}

struct ast_node* ast_assign(struct token name, struct ast_node* value)
{
    struct ast_node* node = ast_node();
    node->type = ASSIGN;
    node->assign = (struct ast_assign*)malloc(sizeof(struct ast_assign));
    node->assign->name = name;
    node->assign->value = value;
    return node;
}


struct ast_node* ast_binary(struct token op, struct ast_node* left, struct ast_node* right)
{
    struct ast_node* node = ast_node();
    node->type = BINARY;

    node->binary = (struct ast_binary*)malloc(sizeof(struct ast_binary));
    node->binary->op = op;
    node->binary->left = left;
    node->binary->right = right;
    return node;
}

struct ast_node* ast_logical(struct token op, struct ast_node* left, struct ast_node* right)
{
    struct ast_node* node = ast_node();
    node->type = LOGICAL;

    node->logical = (struct ast_logical*)malloc(sizeof(struct ast_logical));
    node->logical->op = op;
    node->logical->left = left;
    node->logical->right = right;
    return node;
}

struct ast_node* ast_unary(struct token op, struct ast_node* right)
{
    struct ast_node* node = ast_node();
    node->type = UNARY;
    node->unary = (struct ast_unary*)malloc(sizeof(struct ast_unary));
    node->unary->op = op;
    node->unary->right = right;
    return node;
}

struct ast_node* ast_literal(int literal_type, struct token value)
{
    struct ast_node* node = ast_node();
    node->type = LITERAL;
    node->literal = (struct ast_literal*)malloc(sizeof(struct ast_literal));
    node->literal->literal_type = literal_type;
    node->literal->value = value;
    return node;
}

struct ast_node* ast_variable(struct token value)
{
    struct ast_node* node = ast_node();
    node->type = VARIABLE;
    node->variable = (struct ast_variable*)malloc(sizeof(struct ast_variable));
    node->variable->name = value;
    return node;
}
