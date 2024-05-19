#include "token.h"

struct token* token_create(int type, char* lexeme, unsigned int line)
{
    struct token* token = (struct token*)malloc(sizeof(struct token));
    token->type = type;
    token->line = line;
    token->lexeme = lexeme;

    return token;
}

struct token_list* token_list_init()
{
    struct token_list* new = (struct token_list*)malloc(sizeof(struct token_list));
    new->size = 0;
    new->head = NULL;
}

void token_list_add(struct token_list* list, struct token* token)
{
    struct token_node* new = ( struct token_node*)malloc(sizeof( struct token_node));
    new->next = NULL;
    new->token = token;

    if(list->head == NULL)
    {
        list->head = new;
        list->size += 1;
        return;
    }

    struct token_node* aux = list->head;
    while(aux->next != NULL)
        aux = aux->next;

    aux->next = new;
    list->size += 1;
    return;
}

struct token* token_at(struct token_list* list, int pos)
{
    if(list->head == NULL)
        return NULL;

    if(pos == 0)
        return list->head->token;
    
    struct token_node* aux = list->head;
    int i = 0;
    while(i < pos)
    {
        aux = aux->next;
        i += 1;
    }

    return aux->token;
}
