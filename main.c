//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"


int main(){

    symtable* mySymtable=(symtable*)malloc(sizeof(symtable));
    if (mySymtable == NULL) return INTERNAL_ERROR;
    symtableInit(mySymtable); 

    Token* MyToken = tokenCreate();
    
    tokenScan(stdin,MyToken);
    
    int status;
    Tree *exprTree = (Tree *)malloc(sizeof(Tree));
    status = expressionCheck(MyToken, exprTree);
    if (status == 0){
        status = isExpresionright(exprTree, mySymtable);
        printf("%i", status);
        return status;
    }
    else{
        puts("CHYBA");
        printf("%i", status);
        return status;
    }
}