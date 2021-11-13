#include "Parser.h"


int Parse(TokenList* list){
    Token* MyToken=(Token*)malloc(sizeof(Token));
    NonTerminal MyNonTerminal=condition;
    tokenScan(stdin, list, MyToken);
    if (First(MyToken,MyNonTerminal))
    {
        printf("here");
    }
    return 0;
}
bool First(Token* MyToken, NonTerminal MyNonTerminal){
    if (MyNonTerminal==program){
        return true;
    }
    if (MyNonTerminal==condition){
        return true;
    }
    return false;
}