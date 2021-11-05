#include "stack.h"

void stackPush(stack* myStack, symbol* mySymbol){
    symbol* tmp= myStack->head;
    myStack->head=mySymbol;
    mySymbol->next=tmp;
}
symbol* stackTop(stack)