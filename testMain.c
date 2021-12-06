//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"


int main(){

    symtable* mySymtable=(symtable*)malloc(sizeof(symtable));
    if (mySymtable == NULL) return INTERNAL_ERROR;
    symtableInit(mySymtable); 

    TokenList list;
    listInit(&list);
    Token* MyToken = tokenCreate();
    tokenScan(stdin,&list,MyToken);
    int status;
    Tree *exprTree;
    status = expressionCheck(MyToken,&list, exprTree);
    if (status == 0){
        printf("OK");
        printExpressionTree(exprTree);
        return status;
    }
    else{
        puts("CHYBA");
        printf("%i", status);
        return status;
    }
}