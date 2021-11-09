#include "Parcer.h"
//#include "Scanner.h"
//#include "stack.h"
#define NUMBER_OF_RULES 4






/*
    return:
    1-chcem novy token
    2-koniec analizy


*/
int compare(Token* MyToken, TokenList* list){
    stack* MyStack=(stack*)malloc(sizeof(stack));
    stackInit(MyStack);
    char SymbolNow[1];
    stackPush(MyStack,"$");
    char wannaBeRule[MAX_RULELENGHT];
    int line=0;
    int column=0;
            //zasobnik  +   *   (   )   i   $
    char table[6][6]={{'>','<','<','>','<','>'}, // +
                      {'>','>','<','>','<','>'}, // *
                      {'<','<','<','=','<','0'}, // (
                      {'>','>','0','>','0','>'}, // )
                      {'>','>','0','>','0','>'}, // i
                      {'<','<','<','0','<','0'}};// $
                                               // Token
    char* rules[4]={"E+E","E*E","(E)","i"};
    //printf("%s chiil\n",MyStack->head->Character);
    
    while (true){
        printf("tabulka %i %i\n",topOfStackToLine(MyStack),symbolToColumn(MyToken->type));
        switch (table[topOfStackToLine(MyStack)][symbolToColumn(MyToken->type)])
        {
        case '>':
            topOfStackUntilLB(wannaBeRule,MyStack);
            printf("%i\n",isItRule(rules,wannaBeRule));
            break;

        case '<':
            //printf("scanujem");
            stackPush(MyStack,"<");
            tokenToSymbol(MyToken->type,SymbolNow);
            stackPush(MyStack,SymbolNow);
            MyToken=tokenCreate();
            tokenScan(stdin,list,MyToken);
            break;

        case '=':
            tokenToSymbol(MyToken->type,SymbolNow);
            stackPush(MyStack,SymbolNow);
            tokenScan(stdin,list,MyToken);
            break;
        
        case '0':
            return 1;
            break;

        case '\0':
            return 1;
            break;
        default:
            break;
        }
    }
    return 0;
}
    
int symbolToColumn(char* tokenType){
    if (strcmp(tokenType,"SCITANIE")==0)
    {
        return 0;
    }
    else if (strcmp(tokenType,"NASOBENIE")==0)
    {
        return 1;
    }
    else if (strcmp(tokenType,"LEFT BRACKET")==0)
    {
        return 2;
    }
    else if (strcmp(tokenType,"RIGHT BRACKET")==0)
    {
        return 3;
    }
    else if (strcmp(tokenType,"CELE CISLO")==0) //(strcmp(tokenType,"IDENTIFIKATOR") || strcmp(tokenType,"CELE CISLO") || strcmp(tokenType,"DESATINNY LITERAL"))==0
    {
        return 4;
    }
    else
    {
        return 5;
    }
}
int topOfStackToLine(stack* MyStack){
    char dataptr[2];
    stackTop(MyStack,dataptr);
    //printf("%s %i\n",dataptr,(strcmp(dataptr,"i")));
    if (strcmp(dataptr,"+")==0){
        return 0;
    }
    else if (strcmp(dataptr,"*")==0){
        return 1;
    }
    else if (strcmp(dataptr,"(")==0){
        return 2;
    }
    else if (strcmp(dataptr,")")==0){
        return 3;
    }
    else if (strcmp(dataptr,"i")==0){
        return 4;
    }
    else if (strcmp(dataptr,"$")==0){
        return 5;
    }
    else{
        return 6;
    }
    
}
void tokenToSymbol(char* tokenType, char* symbol){
    //printf("%s",tokenType);
    if (strcmp(tokenType,"SCITANIE")==0)
    {
        strcpy(symbol,"+");
    }
    else if (strcmp(tokenType,"NASOBENIE")==0)
    {
        strcpy(symbol,"*");
    }
    else if (strcmp(tokenType,"LEFT BRACKET")==0)
    {
        strcpy(symbol,"(");
    }
    else if (strcmp(tokenType,"RIGHT BRACKET")==0)
    {
        strcpy(symbol,")");
    }
    else if (strcmp(tokenType,"CELE CISLO")==0)//strcmp(tokenType,"DESATINNY LITERAL" (strcmp(tokenType,"IDENTIFIKATOR") ||
    {
        strcpy(symbol,"i");
    }
    
}
int isItRule(char** rules,char* wannaBeRule){
    for (int i = 0; i < NUMBER_OF_RULES; i++){
        if (strcmp(rules[i],wannaBeRule)==0)
        {
            return i;
        }
    }
    return -1;
}
    
//tabulku pravidle
//fumkcia terminal top stack
//funkcia TOPSECOND



    


