#include "token.h"

struct token token_create(int type, char* lexeme)
{
    struct token token;
    token.type = type;
    token.lexeme = lexeme;

    return token;
}
