#ifndef ENUMS
#define ENUMS

enum type { NUM, BOOL, STRING, VOID };

enum token_type
{
    TOKEN_NUM, TOKEN_ID, TOKEN_TRUE, TOKEN_FALSE,
    TOKEN_VAR, TOKEN_FUNCTION, TOKEN_STRING,

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
    TOKEN_BREAK, TOKEN_CONTINUE, TOKEN_RETURN,

    TOKEN_TYPE_NUM, TOKEN_TYPE_BOOL, TOKEN_TYPE_STRING,

    TOKEN_DOT, TOKEN_COMMA, TOKEN_ARROW, TOKEN_COLON,
    TOKEN_ENDLINE, TOKEN_END
};

#endif