#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "token.h"

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

void expr(struct parser* parser);
void expr_tail(struct parser* parser);
void term(struct parser* parser);
void term_tail(struct parser* parser);
void unary(struct parser* parser);
void factor(struct parser* parser);

#endif