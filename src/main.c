#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "ast.h"

char* read_file(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) 
    {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) 
    {
        fclose(file);
        free(content);
        exit(EXIT_FAILURE);
    }

    content[file_size] = '\0';

    fclose(file);
    return content;
}

void print_tokens(struct token_list* list)
{
    if(list->head == NULL)
        return;

    struct token_node* aux = list->head;
    while(aux->next != NULL)
    {
        printf("Token: [%d, %s, %d]\n", aux->token->type, aux->token->lexeme, aux->token->line);
        aux = aux->next;
    }
    printf("Token: [%d, %s, %d]\n", aux->token->type, aux->token->lexeme, aux->token->line);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *result = strstr(argv[1], ".srn");
    if (result == NULL)
    {
        printf("invalid file.\n");
        exit(1);
    }
    
    char filename[100];
    strcpy(filename, ".//example//");
    strcat(filename, argv[1]);
    
    char* content = read_file(filename);

    struct lexer* lexer = lexer_init(content);
    print_tokens(lexer_read(lexer));
    
    struct parser* parser = parser_init(lexer_read(lexer));
    struct ast_list* statements = parse(parser);

    struct interpreter* interpreter = interpreter_init();
    interpret(interpreter, statements);
    printf("\n");

    return 0;
}
