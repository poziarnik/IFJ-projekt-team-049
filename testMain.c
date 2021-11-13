//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"
int main(){

    TokenList list;
    listInit(&list);
    Token* MyToken = tokenCreate();
    tokenScan(stdin,&list,MyToken);
    compare(MyToken,&list);

return 0;
    
    
}