#ifndef __STACKTREE__

#define __STACKTREE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"
#include "error.h"

typedef enum{
    LESS_MORE_EQUAL_NOTEQUAL,
    CONCATENATION,
    PLUS_MINUS,
    MULTIPLICATION_DIVISION_INTDIV,
    SIZEOF,
    LEFTBRACKET,
    RIGHTBRACKET,
    DATA,
    ELSE,
    NOTERM, 
}precedenceOperators;

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

typedef struct Element{
    precedenceOperators Item;
    struct tree *tree;
    struct Element *next;
}TElement;

typedef struct Stack{
    TElement *top;
}TStack;



void Stack_init(TStack *Stack);
int Stack_push(TStack *Stack, int newItem, Token *token);
void Stack_pop(TStack *Stack);
void Stack_pop_till_bracket(TStack *Stack);
int Stack_first_nonterm(TStack *stack);
void Stack_push_beforeNonterm(TStack *stack);
void Stack_print(TStack *stack);




void TreeInit(Tree **tree);
Tree *treeInsert_BinaryOperator(Tree **tree, TElement *Operator, TElement *Data1, TElement *Data2);
Tree *tree_insert_UnaryOperator(Tree **tree, TElement *Operator, TElement *Data);

#endif // !1