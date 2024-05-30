#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "token.h"
#include "ast.h"

struct parser
{
    struct token_list* tokens;
    unsigned int pos;
};

struct parser* parser_init(struct token_list* list);
int match(struct parser* parser, int type);
int check(struct parser* parser, int type);
struct token* advance(struct parser* parser);
struct token* peek(struct parser* parser);
struct token* previous(struct parser* parser);
struct token* consume(struct parser* parser, int type);

struct ast_node* decl(struct parser* parser);
struct ast_node* fundecl(struct parser* parser);
struct ast_node* vardecl(struct parser* parser);
struct ast_node* stmt(struct parser* parser);
struct ast_node* loop(struct parser* parser);
struct ast_node* _if(struct parser* parser);
struct ast_node* if_tail(struct parser* parser, struct ast_node* condition, struct ast_node* then);
struct ast_node* assign(struct parser* parser);
struct ast_node* _return(struct parser* parser);
struct ast_node* block(struct parser* parser);
struct ast_node* bool(struct parser* parser);
struct ast_node* bool_tail(struct parser* parser, struct ast_node* left);
struct ast_node* join(struct parser* parser);
struct ast_node* join_tail(struct parser* parser, struct ast_node* left);
struct ast_node* equality(struct parser* parser);
struct ast_node* equality_tail(struct parser* parser, struct ast_node* left);
struct ast_node* rel(struct parser* parser);
struct ast_node* rel_tail(struct parser* parser, struct ast_node* left);
struct ast_node* expr(struct parser* parser);
struct ast_node* expr_tail(struct parser* parser, struct ast_node* left);
struct ast_node* term(struct parser* parser);
struct ast_node* term_tail(struct parser* parser, struct ast_node* left);
struct ast_node* unary(struct parser* parser);
struct ast_node* factor(struct parser* parser);

#endif