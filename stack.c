#include "stack.h"


void stackInit(stack *myStack){
    if (myStack != NULL){
        myStack->head=NULL;
    }
    
}
/*
    na vrch stacku pushne character aky potrebujeme.
    pri tom vytvori element strukturi symbol takze treba kontrolovat chybu mallocu
    return:
        0 - vsetko ok
        1 - chyba mallocu
*/
int stackPush(stack* myStack, char* NewChar){
    Symbol* newSymbol=(Symbol*)malloc(sizeof(Symbol));
    if (newSymbol==NULL){
        return 1;
    }
    symbolInit(newSymbol);
    newSymbol->Character=NewChar;
    if (myStack->head!=NULL){
        newSymbol->next=myStack->head->next;
        myStack->head=newSymbol;
    }
    else{
        myStack->head=newSymbol;
    }
    return 0;
}

void symbolInit(Symbol* MySymbol){
    MySymbol->next=NULL;
    MySymbol->Character=NULL;
}
void stackTop(stack *myStack,char* dataptr){
    if (myStack->head != NULL){
        char* Top=myStack->head->Character;
        strcpy(dataptr, Top);
    }
}
void stackTopTerminal(stack *myStack,char* dataptr){
    
    Symbol* tmp = myStack->head;
    while (tmp!=NULL){
        if (strcmp(tmp->Character,"E")==0){
            dataptr=tmp->Character;
            break;
        }
        tmp=tmp->next;
    }
}
    

void stackPop(stack *myStack){
    Symbol* tmp;
    if (myStack->head!=NULL)
    {
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
    
    
}


int topOfStackUntilLB(char* wannaBeRule, stack* MyStack){
    char* symbol;
    for(int i=0;i < MAX_RULELENGHT; i++){
        stackTop(MyStack, symbol);
        if (strcmp(symbol,"<")==0){
            stackPop(MyStack);
            break;
        }
        else if (strcmp(symbol,"$")==0)
        {
            break;
        }
        wannaBeRule[i]=*symbol;
        stackPop(MyStack);
    }
}
