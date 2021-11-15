#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"


typedef struct Element{
    int Item;
    Token *token;
    struct Element *next;
}TElement;

typedef struct Stack{
    TElement *top;
}TStack;

typedef struct tnode{
    Token *token;
    struct tnode *left;
    struct tnode *right;
}Tnode;

void Stack_init(TStack *Stack);
void Stack_push(TStack *Stack, int newItem, Token *token);
void Stack_pop(TStack *Stack);
void Stack_pop_till_bracket(TStack *Stack);
void tree_init(Tnode **tree);
