//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"
int main(){

    TokenList list;
    listInit(&list);
    Token* MyToken = tokenCreate();
    tokenScan(stdin,&list,MyToken);
    int status;
    status = compare(MyToken,&list);
    if (status != 0){
        printf("CHYBA\n");
        printf("%i", status);
    }
    
return 0;
    
    
}