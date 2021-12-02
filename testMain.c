//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"
int main(){

    TokenList list;
    listInit(&list);
    Token* MyToken = tokenCreate();
    tokenScan(stdin,&list,MyToken);
    int status;
    Tree *exprTree;
    status = expressionCheck(MyToken,&list, exprTree);
    if (status == 0){
        puts("---------------------");
        puts("");

        
        
        puts("");
        puts("---------------------");

        
        return 0;
    }
    else{
        puts("CHYBA");
        printf("%i", status);
        return status;
    }
    

    
    
}