#include "stack.h"
int main(){
    stack* MyStack=(stack*)malloc(sizeof(stack));
    stackInit(MyStack);
    for (int i = 5; i > 0; i--)
    {
        symbol* MySymbol=(symbol*)malloc(sizeof(symbol));
        MySymbol->att="asdfas";   
        MySymbol->type="asdasdf";
        stackPush(MyStack, MySymbol);
    }
    
    stackPop(MyStack);
    stackPop(MyStack);
    stackPop(MyStack);
    stackPop(MyStack);
    stackPop(MyStack);
    stackPop(MyStack);

    
    symbol* topsymbol=stackTop(MyStack);
    printf("%i topindex:%i",topsymbol->x, MyStack->topIndex);
}