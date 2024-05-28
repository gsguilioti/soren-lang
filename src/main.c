#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "lexer.h"
#include "parser.h"
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

void print_ast(struct ast_node* node)
{
    if (node == NULL) 
        return;
    
    switch (node->type) 
    {
        case BINARY:
            print_ast(node->binary->left);
            print_ast(node->binary->right);
            printf("%s ", node->binary->op.lexeme);
            break;
        case LOGICAL:
            print_ast(node->logical->left);
            print_ast(node->logical->right);
            printf("%s ", node->logical->op.lexeme);
            break;
        case UNARY:
            printf("%s", node->unary->op.lexeme);
            print_ast(node->unary->right);
            break;
        case LITERAL:
            printf("%s ", node->literal->value.lexeme);
            break;
        case VARIABLE:
            printf("%s ", node->variable->name.lexeme);
            break;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char filename[100];
    strcpy(filename, ".//example//");
    strcat(filename, argv[1]);
    
    char* content = read_file(filename);

    struct lexer* lexer = lexer_init(content);
    print_tokens(lexer_read(lexer));
    
    struct parser* parser = parser_init(lexer_read(lexer));
    struct ast_node* ast = bool(parser);
    print_ast(ast);
    printf("\n");

    return 0;
}
