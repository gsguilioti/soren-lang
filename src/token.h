#ifndef TOKEN_H
#define TOKEN_H

struct token
{
    enum {
        TOKEN_NUM,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_TIMES,
        TOKEN_DIV
    } type;

    char* lexeme;
};

struct token token_create(int type, char* lexeme);

#endif
