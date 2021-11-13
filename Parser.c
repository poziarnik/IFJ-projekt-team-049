#include "Parser.h"


int Parse(TokenList* list){
    Token* MyToken=(Token*)malloc(sizeof(Token));
    //NonTerminal MyNonTerminal=condition;
    tokenScan(stdin, list, MyToken);
    /*if (First(MyToken,MyNonTerminal))
    {
        printf("here");
    }
    return 0;*/

}
bool first(Token* MyToken, NonTerminal MyNonTerminal){
    if (MyNonTerminal==program){
        if(first(MyToken, functionDec)){
            return true;
        }    
    else if (MyNonTerminal==functionDec){
        if (first(MyToken,global_scope))
        {
            return true;
        }
    }
    else if(MyNonTerminal==global_scope){
        if(strcmp(MyToken->att, "global")==0){
            return true;
        }
    }
    return false;
}





bool fc_program(Token* MyToken, TokenList* list){                  //<prolog><code>
    if(first(MyToken, code)){
        fc_code(MyToken, list);
    }
    return true;
}
bool fc_code(Token* MyToken, TokenList* list){                     //<functionDef><code><statement>
    if (first(MyToken, functionDec)){
        fc_functionDec(MyToken, list);
    }
    else{
        return false;
    }
    
    if (first(MyToken, code)){
        fc_code(MyToken, list);
    }
    else{
        return false;
    }

    if (first(MyToken, statement)){
        fc_statement(MyToken, list);
    }
    return true;
}
bool fc_functionDec(Token* MyToken,TokenList* list){              //<global_scope>function<function_iden>(<params>:<returntypes>)
    if (first(MyToken,global_scope)){
        fc_global_scope(MyToken, list);
    }
    else{
        return false;
    }

    if (MyToken->type==L_bracket){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false ;
    } 

    if(first(MyToken, function_iden)){
        fc_functionIden(MyToken, list);
    }
    else{
        return false;
    }

    if (MyToken->type==L_bracket){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if (first(MyToken, params)){
        fc_params(MyToken, list);
    }
    else{
        return false;
    }
    
    if (MyToken->type==Colon){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if(first(MyToken, returnTypes)){
        fc_returnTypes(MyToken, list);
    }
    else{
        return false;
    }
    
    if (MyToken->type==R_bracket){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 
    return true;
}
bool fc_global_scope(Token* MyToken,TokenList* list){
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_functionIden(Token* MyToken,TokenList* list){
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_params(Token* MyToken,TokenList* list){
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_returnTypes(Token* MyToken,TokenList* list){
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_statement(Token* MyToken,TokenList* list){
    tokenScan(stdin, list, MyToken);
    return true;
}