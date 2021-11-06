#include "stack.h"

void stackInit(stack *myStack){
    if (myStack != NULL){
        myStack->topIndex = -1;
    }
    
}

void stackPush(stack* myStack, char* mySymbol){
    if (myStack->topIndex != MAX_STACK){
        myStack->topIndex++;
        myStack->mySymbol[myStack->topIndex] = mySymbol;
    }

}
char *stackTop(stack *myStack){
    if (myStack->topIndex != 0)
    {
        return myStack->mySymbol[myStack->topIndex];
    }
    
    return NULL;
}

void stackPop(stack *myStack){
    if (myStack->topIndex != 0){
        myStack->mySymbol[myStack->topIndex]=NULL;
        myStack->topIndex--;    
    }
    
}


char* symbolCreate(){
    char* NewSymbol;
    NewSymbol = (char*)malloc(sizeof(char));
    if (NewSymbol != NULL){
        tokenInit(NewSymbol);
    }
    return NewSymbol; 
}