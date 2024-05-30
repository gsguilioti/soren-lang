#include "lexer.h"

static int get_type(char op)
{
    switch(op)
    {
        case '+': return TOKEN_PLUS;
        case '-': return TOKEN_MINUS;
        case '*': return TOKEN_MULT;
        case '/': return TOKEN_DIV;
        case '%': return TOKEN_MOD;
        case '=': return TOKEN_ASSIGN;
        case '!': return TOKEN_NOT;
        case '>': return TOKEN_GREAT;
        case '<': return TOKEN_LESS;
        case '&': return TOKEN_BITAND;
        case '|': return TOKEN_BITOR;
        case '^':  return TOKEN_XOR;
    }
}

static int get_equal_type(char op)
{
    switch(op)
    {
        case '+': return TOKEN_PLUSEQUAL;
        case '-': return TOKEN_MINUSEQUAL;
        case '*': return TOKEN_MULTEQUAL;
        case '/': return TOKEN_DIVEQUAL;
        case '%': return TOKEN_MODEQUAL;
        case '=': return TOKEN_EQUAL;
        case '!': return TOKEN_NOTEQUAL;
        case '>': return TOKEN_GTHEN;
        case '<': return TOKEN_LTHEN;
        case '&': return TOKEN_ANDEQUAL;
        case '|': return TOKEN_OREQUAL;
        case '^':  return TOKEN_XOREQUAL;
    }
}

struct lexer* lexer_init(char* content)
{
    struct lexer* lexer = (struct lexer*)malloc(sizeof(struct lexer));

    if(lexer == NULL)
        exit(EXIT_FAILURE);

    lexer->pos = 0;
    lexer->line = 1;
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

    if(isalpha(lexer->current) || lexer->current == '_')
        return lexer_keyword(lexer);

    switch(lexer->current)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '!':
        case '>':
        case '<':
        case '&':
        case '|':
        case '^': 
            return lexer_handle_equality(lexer);
        case '(': return lexer_op(lexer, TOKEN_LPAREN, lexer_tostring_char(lexer));
        case ')': return lexer_op(lexer, TOKEN_RPAREN, lexer_tostring_char(lexer));
        case '{': return lexer_op(lexer, TOKEN_LBRACE, lexer_tostring_char(lexer));
        case '}': return lexer_op(lexer, TOKEN_RBRACE, lexer_tostring_char(lexer));
        case '[': return lexer_op(lexer, TOKEN_LSQUARE, lexer_tostring_char(lexer));
        case ']': return lexer_op(lexer, TOKEN_RSQUARE, lexer_tostring_char(lexer));
        case ';': return lexer_op(lexer, TOKEN_ENDLINE, lexer_tostring_char(lexer));
    }

    printf("Lexical error: symbol not recognized: %c\naborting...\n", lexer->current);
    exit(1);
}

struct token* lexer_op(struct lexer* lexer, int type, char* op)
{
    struct token* token = token_create(type, op, lexer->line);
    lexer_advance(lexer);
    return token;
}

struct token* lexer_handle_equality(struct lexer* lexer)
{
    if(lexer->current == '-')
        return lexer_handle_minus(lexer);

    char* op = calloc(2, sizeof(char));
    op[0] = lexer->current;
    op[1] = '\0';
    lexer_advance(lexer);

    int type;
    if(lexer->current == '=')
        type = get_equal_type(op[0]);
    else if(lexer->current == '&' && op[0] == '&')
        type = TOKEN_AND;
    else if(lexer->current == '|' && op[0] == '|')
        type = TOKEN_OR;
    else
        return token_create(get_type(op[0]), op, lexer->line);

    char* aux = lexer_tostring_char(lexer);
    op = realloc(op, (strlen(op) + strlen(aux) + 1) * sizeof(char));
    strcat(op, aux);
    lexer_advance(lexer);

    return token_create(type, op, lexer->line);
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

struct token* lexer_keyword(struct lexer* lexer)
{
    char* keyword = calloc(2, sizeof(char));
    keyword[0] = lexer->current;
    keyword[1] = '\0';
    lexer_advance(lexer);
    
    while(isalnum(lexer->current))
    {
        char* aux = lexer_tostring_char(lexer);
        keyword = realloc(keyword, (strlen(keyword) + strlen(aux) + 1) * sizeof(char));
        strcat(keyword, aux);

        lexer_advance(lexer);
    }

    if(strcmp(keyword, "true") == 0)
        return token_create(TOKEN_TRUE, keyword, lexer->line);
    else if(strcmp(keyword, "false") == 0)
        return token_create(TOKEN_FALSE, keyword, lexer->line);
    else if(strcmp(keyword, "var") == 0)
        return token_create(TOKEN_VAR, keyword, lexer->line);
    else if(strcmp(keyword, "if") == 0)
        return token_create(TOKEN_IF, keyword, lexer->line);
    else if(strcmp(keyword, "else") == 0)
        return token_create(TOKEN_ELSE, keyword, lexer->line);
    else if(strcmp(keyword, "loop") == 0)
        return token_create(TOKEN_LOOP, keyword, lexer->line);

    return token_create(TOKEN_ID, keyword, lexer->line);
}

struct token* lexer_handle_minus(struct lexer* lexer)
{
    if(lexer->content[lexer->pos+1] == '=')
        return lexer_op(lexer, TOKEN_MINUSEQUAL, "-=");

    return lexer_op(lexer, TOKEN_MINUS, lexer_tostring_char(lexer));
}

char* lexer_tostring_char(struct lexer* lexer)
{
    char* num = malloc(sizeof(2));
    num[0] = lexer->current;
    num[1] = '\0';

    return num;
}
