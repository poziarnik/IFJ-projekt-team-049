#include "stack.h"

/*
    inicializuje element strukturi stack
*/
void stackInit(stack *myStack){
    if (myStack != NULL){
        myStack->head=NULL;
    }
    
}

/*
    Na vrch stacku pushne parameter NewChar.
    Pri tom vytvori element strukturi symbol takze treba kontrolovat chybu mallocu.
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
    strcpy(newSymbol->Character,NewChar);
    //newSymbol->Character=NewChar;
    if (myStack->head!=NULL){
        newSymbol->next=myStack->head;
        myStack->head=newSymbol;
    }
    else{
        myStack->head=newSymbol;
    }
    return 0;
}

/*
    pushne znak |<| na zasobnik. Ak je na vrchole zasobnika E pushne < az na 2. miesto podla algoritmu
    pri tom vytvori element strukturi symbol takze treba kontrolovat chybu mallocu
    return:
        0 - vsetko ok
        1 - chyba mallocu
*/
int stackPushLB(stack* myStack){
    Symbol* newSymbol=(Symbol*)malloc(sizeof(Symbol));
    if (newSymbol==NULL){
        return 1;
    }
    symbolInit(newSymbol);
    strcpy(newSymbol->Character,"<");

    Symbol* tmp=myStack->head;
    if (strcmp(tmp->Character,"E")==0)
    {
        newSymbol->next=tmp->next;
        tmp->next=newSymbol;
    }
    else{
        newSymbol->next=tmp;
        myStack->head=newSymbol;
    }
}

/*
    Inicializuje element strukturi Symbol
*/
void symbolInit(Symbol* MySymbol){
    MySymbol->next=NULL;
    //MySymbol->Character='\0';
}

/*
    Do parametru dataptr vlozi vrchol zasobniku
*/
void stackTop(stack *myStack,char* dataptr){
    if (myStack->head != NULL){
        char* Top=myStack->head->Character;
        strcpy(dataptr, Top);
    }
}

/*
    Do parametru dataptr vlozi prvy terminal pri vrchole zasobniku(ignoruje E)
*/
void stackTopTerminal(stack *myStack,char* dataptr){
    
    Symbol* tmp = myStack->head;
    while (tmp!=NULL){
        if (strcmp(tmp->Character,"E")!=0){
            strcpy(dataptr, tmp->Character);
            break;
        }
        else{
            tmp=tmp->next;
        }
        
    }
}
    
/*
    uvolni vrchol zasobniku
*/
void stackPop(stack *myStack){
    //printf("imhere");
    Symbol* tmp;
    if (myStack->head!=NULL)
    {
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
    
    
}

/*
    Do parametru wannaBeRule nacita vsetko pri vrchole zasobniku po znak <, podla algoritmu.
    Tento parameter bude neskor kontorolovany ci zodpoveda predpisanym pravidlam. 
*/
int topOfStackUntilLB(char* wannaBeRule, stack* MyStack){
    char symbol[MAX_RULELENGHT];
    int symbolLenght=0;
    strcpy(wannaBeRule,"");
    while(true){
        
        stackTop(MyStack, symbol);
        if (strcmp(symbol,"<")==0){
            stackPop(MyStack);
            break;
        }
        else if (strcmp(symbol,"$")==0){
            break;
        }
        else if (symbolLenght==MAX_RULELENGHT){
            return 1;
            break;
        }
        else{
            symbolLenght++;
            strcat(wannaBeRule,symbol);
            stackPop(MyStack);            
        }
        
    }
    return 0;
}

/*
    Zobrazi sucastny stav zasobnika z prava do lava(zatvorky < a > su naopak). 
*/
void stackPrint(stack* MyStack){
    Symbol* tmp=MyStack->head;
    printf("obsah stacku\n");
    while(tmp!=NULL){
        printf("     %s", tmp->Character);
        tmp=tmp->next;
    }
    printf("\n");
}
