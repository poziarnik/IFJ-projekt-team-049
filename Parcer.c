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
    wannaBeRule[0]='\0';
    int line=0;
    int column=0;
               //token  +   *   (   )   i   $
    char table[6][6]={{'>','<','<','>','<','>'}, // +
                      {'>','>','<','>','<','>'}, // *
                      {'<','<','<','=','<','0'}, // (
                      {'>','>','0','>','0','>'}, // )
                      {'>','>','0','>','0','>'}, // i
                      {'<','<','<','0','<','0'}};// $
                                               // Zasobnik
    char* rules[4]={"E+E","E*E","(E)","i"};
    //printf("%s chiil\n",MyStack->head->Character);
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++)
        {
            printf("%c %i %i\n",table[i][j],i,j);
        }
        
    }
    
    
    while (true){
        
        printf("\ntabulka %i %i znak v tabulke |%c|-----------------------------------------\n",topOfStackToLine(MyStack),tokenToColumn(MyToken->type), table[topOfStackToLine(MyStack)][tokenToColumn(MyToken->type)]);
        stackPrint(MyStack);
        printf("stackTop: %s Token: %s\n",MyStack->head->Character,MyToken->type);
        switch (table[topOfStackToLine(MyStack)][tokenToColumn(MyToken->type)])
        {
        case '>':
            topOfStackUntilLB(wannaBeRule,MyStack);
            printf("pravidelo: %i\n",isItRule(rules,wannaBeRule, MyStack));
            break;

        case '<':
            stackPushLB(MyStack);
            SymbolNow[0]='\0';
            tokenToSymbol(MyToken->type,SymbolNow);
            stackPrint(MyStack);
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
            return 1;
            break;
        }
    }
    return 0;
}
/*
    zoberie typ tokenu a vrati odpovedajuce cislo stlpca v precedencnej tabulke ak token neodpoveda ziadnemu symbolu, ktory
    moze byt sucastou expresion vracia stlpec $ ktory znaci koniec expresion
*/
int tokenToColumn(char* tokenType){
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
/*
    zoberie prvy terminal(neberie E) z vrcholu stacku a vrati k nemu odpovedajuci riadok precedencnej tabulky 
*/
int topOfStackToLine(stack* MyStack){
    char dataptr[2];
    stackTopTerminal(MyStack,dataptr);
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
/*
    zoberie typ tokenu a prevedie ho na jednoduchy symbol ktory sa pouziva na zasobniku
*/
void tokenToSymbol(char* tokenType, char* symbol){
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
/*
    skontroluje ci je wannaBeRule nejake pravidlo a nasledne vrati cislo pravidla
*/
int isItRule(char** rules,char* wannaBeRule, stack* MyStack){
    for (int i = 0; i < NUMBER_OF_RULES; i++){
        if (strcmp(rules[i],wannaBeRule)==0)
        {
            stackPush(MyStack, "E");
            return i;
        }
    }
    return -1;
}

//tabulku pravidle
//fumkcia terminal top stack
//funkcia TOPSECOND



    


