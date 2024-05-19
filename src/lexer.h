#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"

struct lexer
{
    int line;
    char current;
    char* content;
    unsigned int pos;
    struct token_list* tokens;
};

struct lexer* lexer_init(char* content);
void lexer_advance(struct lexer* lexer);
void lexer_skip(struct lexer* lexer);
struct token* lexer_collect(struct lexer* lexer);
struct token* lexer_op(struct lexer* lexer, int type, char* op);
struct token* lexer_num(struct lexer* lexer);
struct token* lexer_handle_minus(struct lexer* lexer);
char* lexer_tostring_char(struct lexer* lexer);
struct token_list* lexer_read(struct lexer* lexer);

#endif
