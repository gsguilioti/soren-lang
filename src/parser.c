#include "parser.h"

#include <stdio.h>
#include "token.h"

static void error(struct parser* parser)
{
    struct token* token = token_at(parser->tokens, parser->pos);
    printf("syntax error: token '%s' not expected in line '%d'\n", token->lexeme, token->line);
    exit(1);
}

static int at_end(struct parser* parser)
{
    return peek(parser)->type == TOKEN_END;
}

struct parser* parser_init(struct token_list* list)
{
    struct parser* parser = (struct parser*)malloc(sizeof(struct parser));

    if(parser == NULL)
        exit(EXIT_FAILURE);

    parser->pos = 0;
    parser->tokens = list;
    return parser;
}

int match(struct parser* parser, int type)
{
    if(check(parser, type))
    {
        advance(parser);
        return 1;
    }

    return 0;
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

    error(parser);
}

struct ast_node* bool(struct parser* parser)
{
    struct ast_node* left = join(parser);
    return bool_tail(parser, left);
}

struct ast_node* bool_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_OR))
    {
        struct ast_node* right = join(parser);
        struct ast_node* binary = ast_binary(BINARY, *token, left, right);
        return bool_tail(parser, binary);
    }

    return left;
}

struct ast_node* join(struct parser* parser)
{
    struct ast_node* left = equality(parser);
    return join_tail(parser, left);
}

struct ast_node* join_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_AND))
    {
        struct ast_node* right = equality(parser);
        struct ast_node* binary = ast_binary(BINARY, *token, left, right);
        return join_tail(parser, binary);
    }

    return left;
}

struct ast_node* equality(struct parser* parser)
{
    struct ast_node* left = rel(parser);
    return equality_tail(parser, left);
}

struct ast_node* equality_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_EQUAL) || match(parser, TOKEN_NOTEQUAL))
    {
        struct ast_node* right = rel(parser);
        struct ast_node* binary = ast_binary(BINARY, *token, left, right);
        return equality_tail(parser, binary);
    }

    return left;
}

struct ast_node* rel(struct parser* parser)
{
    struct ast_node* left = expr(parser);
    return rel_tail(parser, left);
}

struct ast_node* rel_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_GREAT) 
    || match(parser, TOKEN_LESS)
    || match(parser, TOKEN_GTHEN)
    || match(parser, TOKEN_LTHEN))
    {
        struct ast_node* right = expr(parser);
        struct ast_node* binary = ast_binary(BINARY, *token, left, right);
        return rel_tail(parser, binary);
    }

    return left;
}

struct ast_node* expr(struct parser* parser)
{
    struct ast_node* left = term(parser);
    return expr_tail(parser, left);
}

struct ast_node* expr_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_PLUS) || match(parser, TOKEN_MINUS))
    {
        struct ast_node* right = term(parser);
        struct ast_node* binary = ast_binary(BINARY, *token, left, right);
        return expr_tail(parser, binary);
    }

    return left;
}

struct ast_node* term(struct parser* parser)
{
    struct ast_node* left = factor(parser);
    return term_tail(parser, left);
}

struct ast_node* term_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_MULT) || match(parser, TOKEN_DIV))
    {
        struct ast_node* right = factor(parser);
        struct ast_node* binary = ast_binary(BINARY, *token, left, right);
        return term_tail(parser, binary);
    }

    return left;
}

struct ast_node* factor(struct parser* parser)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_NUM))
    {
        return ast_primary(NUMBER, *token);
    }
    else if(match(parser, TOKEN_ID))
    {
        return ast_primary(NUMBER, *token);
    }
    else if(match(parser, TOKEN_TRUE) || match(parser, TOKEN_FALSE))
    {
        return ast_primary(NUMBER, *token);
    }
    else if(match(parser, TOKEN_NOT))
    {
        struct ast_node* num = factor(parser);
        int aux = atoi(num->primary->value.lexeme);
        if(aux)
        {
            free(num->primary->value.lexeme);
            num->primary->value.lexeme = "0";
            return num;
        }
        num->primary->value.lexeme = "1";
        return num;
    }
    else if(match(parser, TOKEN_LPAREN))
    {
        struct ast_node* expression = expr(parser);
        consume(parser, TOKEN_RPAREN);
        return expression;
    }
    else
        error(parser);
}
