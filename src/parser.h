#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "token.h"

struct parser
{
    struct token_list* tokens;
    unsigned int pos;
};

int match(struct parser* parser, int type);
int check(struct parser* parser, int type);
struct token* advance(struct parser* parser);
struct token* peek(struct parser* parser);
struct token* previous(struct parser* parser);
struct token* consume(struct parser* parser, int type);

#endif