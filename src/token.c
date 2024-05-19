#include "token.h"

struct token* token_create(int type, char* lexeme)
{
    struct token* token = (struct token*)malloc(sizeof(struct token));
    token->type = type;
    token->lexeme = lexeme;

    return token;
}
