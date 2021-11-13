#include "Parser.h"


int Parse(TokenList* list){
    Token* MyToken=(Token*)malloc(sizeof(Token));
    tokenScan(stdin, list, MyToken);
    if (fc_program(MyToken, list))
    {
        return 1;
    }
    
    return 0;
}
bool first(Token* MyToken, NonTerminal MyNonTerminal){
    if (MyNonTerminal==program){
        if(first(MyToken, code)){
            return true;
        }
    }
    else if (MyNonTerminal==code){
        if(first(MyToken, functionDec)){
            return true;
        }
    }
    else if (MyNonTerminal==functionDec){
        if (first(MyToken,global_scope)){
            return true;
        }
    }
    else if(MyNonTerminal==global_scope){
        if(strcmp(MyToken->att, "global")==0){
            return true;
        }
    }
    else if(MyNonTerminal==function_iden){
        if(MyToken->type==Identifier){
            return true;
        }
    }
    else if(MyNonTerminal==params){
        if(MyToken->type==Identifier){
            return true;
        }
    }
    else if(MyNonTerminal==returnTypes){
        /*if(strcmp(MyToken->att,"integer")==0){
            return true;
        }
        else if(strcmp(MyToken->att,"number")==0){
            return true;
        }
        else if(strcmp(MyToken->att,"string")==0){
            return true;
        }*/
        if(isTokenType(MyToken)){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==param){
        if (MyToken->type==Identifier){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==nextParam){
        if (first(MyToken, param)){
            return true;
        }
        else{
            return false;
        }
    }
    
    return false;
}





bool fc_program(Token* MyToken, TokenList* list){                  //<prolog><code>
    if(first(MyToken, code)){
        return fc_code(MyToken, list);
    }
    else{
        return false;
    }
    
    return true;
}
bool fc_code(Token* MyToken, TokenList* list){                     //<functionDec><code><statement>
    if (first(MyToken, functionDec)){
        fc_functionDec(MyToken, list);
    }
    else{
        return false;
    }
    
    if (first(MyToken, code)){
        fc_code(MyToken, list);
    }

    if (first(MyToken, statement)){
        fc_statement(MyToken, list);
    }
    
    return true;
}
bool fc_functionDec(Token* MyToken,TokenList* list){              //<global_scope>function<function_iden>(<params>:<returntypes>)
    /*if (first(MyToken,global_scope)){
        /*tokenScan(stdin, list, MyToken);
        printf("%s\n",MyToken->att);
        return fc_global_scope(MyToken, list) && \
        chackStr(MyToken, list, "function") && fc_functionIden(MyToken, list) && \
        chackType(MyToken, list, L_bracket) && fc_params(MyToken, list) && \
        chackType (MyToken, list, Colon) && fc_returnTypes(MyToken, list) && \
        chackType(MyToken, list, R_bracket);     
        return true;                       
    }
    else{
        return false;
    }*/
    if (first(MyToken,global_scope)){
        fc_global_scope(MyToken, list);
    }

    if (chackStr(MyToken, list, "function")){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if(first(MyToken, function_iden)){
        fc_functionIden(MyToken, list);
    }
    else{
        return false;
    }

    if (MyToken->type==L_bracket){
        printf("%s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if (first(MyToken, params)){
        fc_params(MyToken, list);
    }
    
    if (MyToken->type==Colon){
        printf("%s\n",MyToken->att);
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
        printf("%s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 
    return true;
}
bool fc_global_scope(Token* MyToken,TokenList* list){                   //global
    if (chackStr(MyToken,list,"global"))
    {
        printf("global_scope: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    
    
    return true;
}
bool fc_functionIden(Token* MyToken,TokenList* list){                   //<functionIden>
    if (MyToken->type==Identifier){
        printf("functionIden: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    }
    return true;
}
bool fc_params(Token* MyToken,TokenList* list){                         //<param><nextParam>
    
    if(first(MyToken, param)){
        fc_param(MyToken, list);
    }
    else{
        return false;
    }

    if(first(MyToken, nextParam)){
        fc_nextParam(MyToken, list);
    }

    /*printf("params: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);*/
    return true;
}
bool fc_param(Token* MyToken,TokenList* list){                          //<identifier>:<type>
    if(MyToken->type==Identifier){
        printf("identifier : %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }   

    if (chackStr(MyToken, list, ":")){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if(isTokenType(MyToken)){
        printf("param: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
        return true;
    }
    else{
        return false;
    }

    return true;
}
bool fc_nextParam(Token* MyToken,TokenList* list){                      //<param>,<nextparam>
    if (first(MyToken, param)){
        fc_param(MyToken, list);
    }
    else{
        return false;
    }

    if (chackStr(MyToken, list, ",")){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    }     

    if (first(MyToken, nextParam)){
        fc_nextParam(MyToken, list);
    }

    return true;
}
bool fc_returnTypes(Token* MyToken,TokenList* list){
    printf("returnTypes: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_statement(Token* MyToken,TokenList* list){
    printf("statemnet: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);
    return true;
}
bool chackType(Token* MyToken, TokenList* list, Token_type checkType){
    printf("TypeCheck: %s\n",MyToken->att);
    if (MyToken->type==checkType){
        tokenScan(stdin, list, MyToken);
        return true;
    }
    else{
        return false;
    }
    
    
}
bool chackStr(Token* MyToken, TokenList* list, char* checkType){
    printf("StringCheck: %s\n",MyToken->att);
    if (strcmp(MyToken->att,checkType)==0){
        return true;
    }
    else{
        return false;
    }
}
bool isTokenType(Token* MyToken){
    if(strcmp(MyToken->att,"integer")==0){
        return true;
    }
    else if(strcmp(MyToken->att,"number")==0){
        return true;
    }
    else if(strcmp(MyToken->att,"string")==0){
        return true;
    }
}