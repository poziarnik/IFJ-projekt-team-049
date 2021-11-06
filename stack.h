#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 20

typedef struct Symbol {        //token
    char* type;                   //typ tokenu
    char* att;              //bude nutne alokovat pamet
}symbol;

typedef struct{
    symbol *mySymbol[MAX_STACK];
    int topIndex; 
}stack;

void stackInit(stack *myStack);
void stackPush(stack* myStack, symbol* mySymbol);
symbol *stackTop(stack *myStack);
void stackPop(stack *myStack);
