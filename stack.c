#include "stack.h"

void stackInit(stack *myStack){
    if (myStack != NULL){
        myStack->topIndex = 0;
    }
    
}

void stackPush(stack* myStack, symbol* mySymbol){
    if (myStack->topIndex != MAX_STACK){
        myStack->topIndex++;
        myStack->mySymbol = mySymbol; //TODO
    }

}
symbol *stackTop(stack *myStack){
    return &(myStack->mySymbol);
}

void stackPop(stack *myStack){
    if (myStack->topIndex != 0){
        myStack->topIndex--;    
    }
}