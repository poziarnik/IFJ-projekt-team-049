//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"
int main(){

    TokenList list;
    listInit(&list);
    Token* MyToken = tokenCreate();
    tokenScan(stdin,&list,MyToken);
    int status;
    status = expressionCheck(MyToken,&list);
    if (status == 0){
        return 0;
    }
    else{
        puts("CHYBA");
        printf("%i", status);
        return status;
    }
    

    
    
}