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

struct token* next(struct parser* parser)
{
    if(at_end(parser))
        return NULL;

    return token_at(parser->tokens, parser->pos +1);
}

struct token* consume(struct parser* parser, int type)
{
    if(check(parser, type))
        return advance(parser);

    error(parser);
}

struct ast_node* decl(struct parser* parser)
{
    if(at_end(parser))
        return NULL;
    else if(match(parser, TOKEN_VAR))
        return vardecl(parser);
    else if(match(parser, TOKEN_FUNCTION))
        return fundecl(parser);

    error(parser);
}

struct ast_node* fundecl(struct parser* parser)
{
    struct token* name = consume(parser, TOKEN_ID);
    consume(parser, TOKEN_LPAREN);
    struct token_list* params = token_list_init();
    if(!check(parser, TOKEN_RPAREN))
    {
        do
        {
            token_list_add(params, consume(parser, TOKEN_ID));
        }
        while(match(parser, TOKEN_COMMA));
    }
    
    consume(parser, TOKEN_RPAREN);
    consume(parser, TOKEN_LBRACE);
    struct ast_node* body = block(parser);
    return ast_function(*name, params, body->block->statements);
}

struct ast_node* vardecl(struct parser* parser)
{
    struct token* name = consume(parser, TOKEN_ID);
    struct ast_node* initializer = NULL;
    if(match(parser, TOKEN_ASSIGN))
        initializer = bool(parser);
    
    consume(parser, TOKEN_ENDLINE);
    return ast_vardecl(*name, initializer);
}

struct ast_node* stmt(struct parser* parser)
{
    if(match(parser, TOKEN_LBRACE))
        return block(parser);
    else if(match(parser, TOKEN_IF))
        return _if(parser);
    else if(match(parser, TOKEN_LOOP))
        return loop(parser);
    else if(match(parser, TOKEN_RETURN))
        return _return(parser);
    else if(match(parser, TOKEN_BREAK))
    {
        consume(parser, TOKEN_ENDLINE);     
        return ast_break();
    }
    else if(match(parser, TOKEN_CONTINUE))
    {
        consume(parser, TOKEN_ENDLINE);        
        return ast_continue();
    }

    return assign(parser);
}

struct ast_node* loop(struct parser* parser)
{
    consume(parser, TOKEN_LPAREN);
    struct ast_node* condition = bool(parser);
    consume(parser, TOKEN_RPAREN);
    struct ast_node* body = stmt(parser);
    return ast_loop(condition, body);
}

struct ast_node* _if(struct parser* parser)
{
    consume(parser, TOKEN_LPAREN);
    struct ast_node* condition = bool(parser);
    consume(parser, TOKEN_RPAREN);
    struct ast_node* then = stmt(parser);
    return if_tail(parser, condition, then);
}

struct ast_node* if_tail(struct parser* parser, struct ast_node* condition, struct ast_node* then)
{
    struct ast_node* _else = NULL;
    if(match(parser, TOKEN_ELSE))
        _else = stmt(parser);

    return ast_if(condition, then, _else);
}

struct ast_node* assign(struct parser* parser)
{
    struct token* name = peek(parser);
    struct ast_node* value = bool(parser);

    if(match(parser, TOKEN_ASSIGN))
    {
        value = bool(parser);
        consume(parser, TOKEN_ENDLINE);
        return ast_assign(*name, value);
    }

    return value;
}

struct ast_node* _return(struct parser* parser)
{
    struct token* keyword = previous(parser);
    struct ast_node* value = NULL;
    if(!check(parser, TOKEN_ENDLINE))
    {
        value = assign(parser);
        return ast_return(*keyword, value);
    }

    consume(parser, TOKEN_ENDLINE);
    return ast_return(*keyword, value);
}

struct ast_node* block(struct parser* parser)
{
    struct ast_list* statements = ast_list_init();
    while(peek(parser)->type != TOKEN_RBRACE)
    {
        if(match(parser, TOKEN_VAR))
            ast_list_add(statements, vardecl(parser));
        else
            ast_list_add(statements, stmt(parser));
    }
    consume(parser, TOKEN_RBRACE);
    return ast_block(statements);
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
        struct ast_node* logical = ast_logical(*token, left, right);
        return bool_tail(parser, logical);
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
        struct ast_node* logical = ast_logical(*token, left, right);
        return join_tail(parser, logical);
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
        struct ast_node* logical = ast_logical(*token, left, right);
        return equality_tail(parser, logical);
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
        struct ast_node* logical = ast_logical(*token, left, right);
        return rel_tail(parser, logical);
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
        struct ast_node* binary = ast_binary(*token, left, right);
        return expr_tail(parser, binary);
    }

    return left;
}

struct ast_node* term(struct parser* parser)
{
    struct ast_node* left = unary(parser);
    return term_tail(parser, left);
}

struct ast_node* term_tail(struct parser* parser, struct ast_node* left)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_MULT) || match(parser, TOKEN_DIV))
    {
        struct ast_node* right = unary(parser);
        struct ast_node* binary = ast_binary(*token, left, right);
        return term_tail(parser, binary);
    }

    return left;
}

struct ast_node* unary(struct parser* parser)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_NOT) || match(parser, TOKEN_MINUS))
        return ast_unary(*token, primary(parser));

    return call(parser);
}

//need to implement dot(call member)
struct ast_node* call(struct parser* parser)
{
    struct ast_node* prim = primary(parser);
    while(1)
    {
        if(match(parser, TOKEN_LPAREN))
            prim = finish_call(parser, prim);
        else break;
    } 

    return prim;
}

struct ast_node* finish_call(struct parser* parser, struct ast_node* calee)
{
    unsigned short count = 0;
    struct ast_list* arguments = ast_list_init();
    if(!check(parser, TOKEN_RPAREN))
    {
        do
        {
            if(count >= 255)
            {
                printf("Can't have more than 255 arguments\n");
                exit(1);
            }

            ast_list_add(arguments, assign(parser));
            count++;

        } while(match(parser, TOKEN_COMMA));
    }

    struct token* paren = consume(parser, TOKEN_RPAREN);
    return ast_call(*paren, calee, arguments);
}


struct ast_node* primary(struct parser* parser)
{
    struct token* token = peek(parser);
    if(match(parser, TOKEN_NUM))
    {
        return ast_literal(INT, *token);
    }
    else if(match(parser, TOKEN_ID))
    {
        return ast_variable(*token);
    }
    else if(match(parser, TOKEN_TRUE) || match(parser, TOKEN_FALSE))
    {
        return ast_literal(BOOL, *token);
    }
    else if(match(parser, TOKEN_LPAREN))
    {
        struct ast_node* expression = expr(parser);
        consume(parser, TOKEN_RPAREN);
        return expression;
    }
    else if(match(parser, TOKEN_STRING))
    {
        return ast_literal(STRING, *token);
    }
    else
        error(parser);
}
