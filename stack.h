#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 20


typedef struct{
    char *mySymbol[MAX_STACK];
    int topIndex; 
}stack;

void stackInit(stack *myStack);
void stackPush(stack* myStack, char* mySymbol);
char *stackTop(stack *myStack);
void stackPop(stack *myStack);
