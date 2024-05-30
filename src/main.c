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

void print_spaces(int space)
{
    for (int i = 10; i < space; i++) 
        printf("  ");
}

void print_ast(struct ast_node* node, int space, int unary)
{
    if (node == NULL) {
        return;
    }

    space += 10;

    switch (node->type)
    {
        case BINARY:
            print_ast(node->binary->right, space, 0);
            print_spaces(space);
            printf("%s\n", node->binary->op.lexeme);
            print_ast(node->binary->left, space, 0);
            break;
        case LOGICAL:
            print_ast(node->logical->right, space, 0);
            print_spaces(space);
            printf("%s\n", node->logical->op.lexeme);
            print_ast(node->logical->left, space, 0);
            break;
        case UNARY:
            print_spaces(space);
            printf("%s", node->unary->op.lexeme);
            print_ast(node->unary->right, space, 1);
            break;
        case LITERAL:
            if(!unary)
                print_spaces(space);
            printf("%s\n", node->literal->value.lexeme);
            break;
        case VARIABLE:
            if(!unary)
                print_spaces(space);
            printf("%s\n", node->variable->name.lexeme);
            break;
        case ASSIGN:
            print_ast(node->assign->value, space, 0);
            print_spaces(space);
            printf("=\n");
            print_spaces(space+10);
            printf("%s\n", node->assign->name.lexeme);
            break;
        case VARDECL:
            print_ast(node->vardecl->initializer, space, 0);
            print_spaces(space);
            printf("vardecl\n");
            print_spaces(space+10);
            printf("%s\n", node->vardecl->name.lexeme);
            break;
        default:
            exit(1);
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
    struct ast_node* statement = decl(parser);
    while(statement != NULL)
    {
        //print_ast(statement, 0, 0);
        statement = decl(parser);
    }
    printf("\n");

    return 0;
}
