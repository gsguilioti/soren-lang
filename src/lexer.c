#include "lexer.h"

struct lexer* lexer_init(char* content)
{
    struct lexer* lexer = (struct lexer*)malloc(sizeof(struct lexer));

    if(lexer == NULL)
    {
        exit(EXIT_FAILURE);
    }

    lexer->pos = 0;
    lexer->line = 0;
    lexer->current = content[lexer->pos];
    lexer->content = content;
    lexer->tokens = token_list_init();
    return lexer;
}

void lexer_advance(struct lexer* lexer)
{
    if(lexer->current != EOF && lexer->pos < strlen(lexer->content))
    {
        lexer->pos += 1;
        lexer->current = lexer->content[lexer->pos];
    }
}

void lexer_skip(struct lexer* lexer)
{
    while(isspace(lexer->current))
    {
        if(lexer->current == '\n')
            lexer->line +=1;
        lexer_advance(lexer);
    }
}

struct token_list* lexer_read(struct lexer* lexer)
{
    while(lexer->current != EOF && lexer->pos < strlen(lexer->content))
        token_list_add(lexer->tokens, lexer_collect(lexer));

    token_list_add(lexer->tokens, token_create(TOKEN_END, "$", lexer->line+1));
    return lexer->tokens;
}

struct token* lexer_collect(struct lexer* lexer)
{
    if(isspace(lexer->current))
        lexer_skip(lexer);

    if(isdigit(lexer->current))
        return lexer_num(lexer);

    switch(lexer->current)
    {
        case '+': return lexer_op(lexer, TOKEN_PLUS, lexer_tostring_char(lexer));
        case '-': return lexer_handle_minus(lexer);
        case '*': return lexer_op(lexer, TOKEN_TIMES, lexer_tostring_char(lexer));
        case '/': return lexer_op(lexer, TOKEN_DIV,   lexer_tostring_char(lexer));
        case '(': return lexer_op(lexer, TOKEN_LPAREN, lexer_tostring_char(lexer));
        case ')': return lexer_op(lexer, TOKEN_RPAREN, lexer_tostring_char(lexer));
    }

    return NULL;
}

struct token* lexer_op(struct lexer* lexer, int type, char* op)
{
    struct token* token = token_create(type, op, lexer->line);
    lexer_advance(lexer);
    return token;
}

struct token* lexer_num(struct lexer* lexer)
{
    char* num = calloc(2, sizeof(char));
    num[0] = lexer->current;
    num[1] = '\0';
    lexer_advance(lexer);
    
    while(isdigit(lexer->current))
    {
        char* aux = lexer_tostring_char(lexer);
        num = realloc(num, (strlen(num) + strlen(aux) + 1) * sizeof(char));
        strcat(num, aux);

        lexer_advance(lexer);
    }

    return token_create(TOKEN_NUM, num, lexer->line);
}

struct token* lexer_handle_minus(struct lexer* lexer)
{
    if(isdigit(lexer->content[lexer->pos+1]))
        return lexer_num(lexer);

    return lexer_op(lexer, TOKEN_MINUS, lexer_tostring_char(lexer));
}

char* lexer_tostring_char(struct lexer* lexer)
{
    char* num = malloc(sizeof(2));
    num[0] = lexer->current;
    num[1] = '\0';

    return num;
}
