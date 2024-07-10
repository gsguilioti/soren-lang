#include "ast.h"

static struct ast_node* ast_node()
{
    struct ast_node* new = (struct ast_node*)malloc(sizeof(struct ast_node));
    if(new == NULL)
        return NULL;

    return new;
}

struct ast_node* ast_function(struct token name, struct token_list* params, struct ast_list* body)
{
    struct ast_node* node = ast_node();
    node->type = FUNDECL;
    node->function = (struct ast_function*)malloc(sizeof(struct ast_function));
    node->function->name = name;
    node->function->params = params;
    node->function->body = body;
    return node;
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

struct ast_node* ast_loop(struct ast_node* condition, struct ast_node* body)
{
    struct ast_node* node = ast_node();
    node->type = LOOP;
    node->loop = (struct ast_loop*)malloc(sizeof(struct ast_loop));
    node->loop->condition = condition;
    node->loop->body = body;
    return node;
}


struct ast_node* ast_if(struct ast_node* condition, struct ast_node* then, struct ast_node* _else)
{
    struct ast_node* node = ast_node();
    node->type = IF;
    node->_if = (struct ast_if*)malloc(sizeof(struct ast_if));
    node->_if->condition = condition;
    node->_if->then = then;
    node->_if->_else = _else;
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

struct ast_node* ast_return(struct token name, struct ast_node* value)
{
    struct ast_node* node = ast_node();
    node->type = RETURN;
    node->_return = (struct ast_return*)malloc(sizeof(struct ast_return));
    node->_return->name = name;
    node->_return->value = value;
    return node;
}

struct ast_node* ast_block(struct ast_list* statements)
{
    struct ast_node* node = ast_node();
    node->type = BLOCK;
    node->block = (struct ast_block*)malloc(sizeof(struct ast_block));
    node->block->statements = statements;
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

struct ast_node* ast_call(struct token paren, struct ast_node* calee, struct ast_list* arguments)
{
    struct ast_node* node = ast_node();
    node->type = CALL;
    node->call = (struct ast_call*)malloc(sizeof(struct ast_call));
    node->call->paren = paren;
    node->call->calee = calee;
    node->call->arguments = arguments;
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

struct ast_node* ast_break()
{
    struct ast_node* node = malloc(sizeof(struct ast_node));
    node->type = BREAK;
    return node;
}

struct ast_node* ast_continue()
{
    struct ast_node* node = malloc(sizeof(struct ast_node));
    node->type = CONTINUE;
    return node;
}

/* 
* =======================
* ast list implementation
* =======================
*/
struct ast_list* ast_list_init()
{
    struct ast_list* new = (struct ast_list*)malloc(sizeof(struct ast_list));
    new->size = 0;
    new->head = NULL;
}

void ast_list_add(struct ast_list* list, struct ast_node* node)
{
    struct ast_list_node* new = (struct ast_list_node*)malloc(sizeof(struct ast_list_node));
    new->next = NULL;
    new->value = node;

    if(list->head == NULL)
    {
        list->head = new;
        list->size += 1;
        return;
    }

    struct ast_list_node* aux = list->head;
    while(aux->next != NULL)
        aux = aux->next;

    aux->next = new;
    list->size += 1;
    return;
}
