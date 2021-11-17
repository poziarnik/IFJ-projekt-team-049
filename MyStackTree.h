#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"
#include "error.h"


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
int Stack_first_nonterm(TStack *stack);
void Stack_push_beforeNonterm(TStack *stack);
void Stack_print(TStack *stack);


typedef struct tree{
    Token *Data;
    union {
        struct {
            struct tree *left;
            struct tree *right;
        } binary;
        struct {
            struct tree *child;
        } unary;    
    } attr;
}Tree;

void treeInit(Tree **tree);
Tree *treeInsert_BinaryOperator(Tree **tree, TElement *Operator, TElement *Data1, TElement *Data2);
Tree *tree_insert_UnaryOperator(Tree **tree, TElement *Operator, TElement *Data);

