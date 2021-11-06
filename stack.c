#include "stack.h"

void stackInit(stack *myStack){
    if (myStack != NULL){
        myStack->topIndex = -1;
    }
    
}

void stackPush(stack* myStack, symbol* mySymbol){
    if (myStack->topIndex != MAX_STACK){
        myStack->topIndex++;
        myStack->mySymbol[myStack->topIndex] = mySymbol; //TODO
    }

}
symbol *stackTop(stack *myStack){
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

void symbolInit(symbol* MySymbol){
    MySymbol->att="";
    MySymbol->type="";
}

symbol* symbolCreate(){
    symbol* NewSymbol;
    NewSymbol = (symbol*)malloc(sizeof(symbol));
    if (NewSymbol != NULL){
        tokenInit(NewSymbol);
    }
    return NewSymbol; 
