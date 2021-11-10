#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK 20
#define MAX_RULELENGHT 4

typedef struct SymbolOfStack{
    char Character[10];
    struct SymbolOfStack *next;
}Symbol;

typedef struct bigStack{
    struct SymbolOfStack* head; 
}stack;




void stackInit(stack *myStack);
int stackPush(stack* myStack, char* NewChar);
int stackPushLB(stack* myStack);
void symbolInit(Symbol* MySymbol);
void stackTop(stack *myStack,char* dataptr);
void stackTopTerminal(stack *myStack,char* dataptr);
int topOfStackUntilLB(char* wannaBeRule, stack* MyStack);
void stackPop(stack *myStack);
char* symbolCreate();
void stackPrint(stack* MyStack);
