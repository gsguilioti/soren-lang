#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

enum token_type
{
    TOKEN_NUM,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_TIMES,
    TOKEN_DIV,
    TOKEN_END
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
