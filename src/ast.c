#include "ast.h"

static struct ast_node* ast_node()
{
    struct ast_node* new = (struct ast_node*)malloc(sizeof(struct ast_node));
    if(new == NULL)
        return NULL;

    return new;
}

struct ast_node* ast_binary(int type, struct token op, struct ast_node* left, struct ast_node* right)
{
    struct ast_node* node = ast_node();
    node->type = BINARY;

    node->binary = (struct ast_binary*)malloc(sizeof(struct ast_binary));
    node->binary->op = op;
    node->binary->left = left;
    node->binary->right = right;
    return node;
}

struct ast_node* ast_primary(int type, struct token value)
{
    struct ast_node* node = ast_node();
    node->type = NUMBER;
    node->primary = (struct ast_primary*)malloc(sizeof(struct ast_primary));
    node->primary->value = value;
    return node;
}
