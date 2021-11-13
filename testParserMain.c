#include "Parser.h"
//#include "Scanner.h"
int main(){
    printf("Meky Zbirka\n");
    TokenList *list=(TokenList*)malloc(sizeof(TokenList));
    listInit(list);
    if(Parse(list)==1){
        printf("got it");
    }
    else{
        printf("to si dojebal");
    }

    return 0;
}