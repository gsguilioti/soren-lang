#include "parser.h"

#include <stdio.h>
#include "token.h"

static void error(struct parser* parser)
{
    struct token* token = token_at(parser->tokens, parser->pos);
    printf("syntax error\ntoken not expected: %s in line %d", token->lexeme, token->line);
    exit(1);
}

static int at_end(struct parser* parser)
{
    return peek(parser)->type == TOKEN_END;
}

int match(struct parser* parser, int type)
{
    if(check(parser, type))
    {
        advance(parser);
        return 1;
    }

    error(parser);
}

int check(struct parser* parser, int type)
{
    if(at_end(parser))
        return 0;

    return peek(parser)->type == type;
}

struct token* advance(struct parser* parser)
{
    if(!at_end(parser))
        ++parser->pos;

    return previous(parser);
}

struct token* peek(struct parser* parser)
{
    return token_at(parser->tokens, parser->pos);
}

struct token* previous(struct parser* parser)
{
    return token_at(parser->tokens, parser->pos -1);
}

struct token* consume(struct parser* parser, int type)
{
    if(check(parser, type))
        return advance(parser);

    exit(1);
}
