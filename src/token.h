#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

enum token_type
{
    TOKEN_NUM, TOKEN_ID, TOKEN_TRUE, TOKEN_FALSE,
    TOKEN_VAR,

    TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_LSQUARE, 
    TOKEN_RSQUARE, TOKEN_LBRACE, TOKEN_RBRACE,

    TOKEN_PLUS, TOKEN_MINUS, TOKEN_MULT, TOKEN_DIV, TOKEN_MOD,

    TOKEN_NOT, TOKEN_GREAT, TOKEN_LESS, TOKEN_GTHEN, 
    TOKEN_LTHEN, TOKEN_EQUAL, TOKEN_NOTEQUAL, TOKEN_AND, 
    TOKEN_OR, TOKEN_XOR, TOKEN_BITAND, TOKEN_BITOR,

    TOKEN_ASSIGN, TOKEN_PLUSEQUAL, TOKEN_MINUSEQUAL, 
    TOKEN_MULTEQUAL, TOKEN_DIVEQUAL, TOKEN_MODEQUAL, 
    TOKEN_ANDEQUAL, TOKEN_OREQUAL, TOKEN_XOREQUAL,

    TOKEN_IF, TOKEN_ELSE, TOKEN_LOOP,

    TOKEN_ENDLINE, TOKEN_END
};

struct token
{
    enum token_type type;
    char* lexeme;
    unsigned int line;
};

struct token* token_create(int type, char* lexeme, unsigned int line);

struct token_node
{
    struct token* token;
    struct token_node* next;
};

struct token_list
{
    struct token_node* head;
    size_t size;
};

struct token_list* token_list_init();
void token_list_add(struct token_list* list, struct token* token);
struct token* token_at(struct token_list* list, int pos);

#endif
