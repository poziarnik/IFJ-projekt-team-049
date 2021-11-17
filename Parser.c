#include "Parser.h"


int Parse(TokenList* list){
    Token* MyToken=(Token*)malloc(sizeof(Token));
    tokenScan(stdin, list, MyToken);
    if (fc_program(MyToken, list)){
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
        if (MyToken->type==Colon){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==nextType){
        if (MyToken->type==Comma){
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
        if (MyToken->type==Comma){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==statement){
        if (first(MyToken, condition)){
            return true;
        }
        if (first(MyToken, loop)){
            return true;
        }
        else if(first(MyToken, define)){
            return true;
        }
        if (first(MyToken, assigne)){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==condition){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->att,"if")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==loop){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->att,"while")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
        
    }
    else if (MyNonTerminal==define){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->att,"local")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else if (MyNonTerminal==assigne){
        if (first(MyToken,varlist)){
            return true;
        }
        else{
            return false;
        }
    }
    else if (MyNonTerminal==varlist){
        if (first(MyToken,var)){
            return true;
        }
        else{
            return false;
        }
    }
    else if (MyNonTerminal==var)
    {
        if(isTokenType(MyToken)){
            return true;
            //printf("kokot\n");
        }
        else{
            return false;
        }
    }
    
    
    
    
    
    
    return false;
}





bool fc_program(Token* MyToken, TokenList* list){                  //program: <prolog><code>
    if(first(MyToken, code)){
        return fc_code(MyToken, list);
    }
    else{
        return false;
    }
    
    return true;
}
bool fc_code(Token* MyToken, TokenList* list){                     //code: <functionDec><code><statement>
    if (first(MyToken, functionDec)){
        if(!fc_functionDec(MyToken, list)){
            return false;
        }
    }
    else{
        return false;
    }
    
    if (first(MyToken, code)){
        if(!fc_code(MyToken, list)){
            return false;
        }
        else{
            return false;
        }
        
    }

    if (first(MyToken, statement)){
        if(!fc_statement(MyToken, list)){
            return false;
        }
        else{
            return false;
        }
        
    }
    
    return true;
}
bool fc_functionDec(Token* MyToken,TokenList* list){              //functionDec: <global_scope>function<function_iden>(<params><returntypes>)
    /*if (first(MyToken,global_scope)){
        tokenScan(stdin, list, MyToken);
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
        if(!fc_global_scope(MyToken, list)){
            return false;
        }
    }

    if (chackStr(MyToken, list, "function")){
        printf("String: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if(first(MyToken, function_iden)){
        if(!fc_functionIden(MyToken, list)){
            return false;
        }
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
        if(!fc_params(MyToken, list)){
            return false;
        }
    }
    
    if (MyToken->type==R_bracket){
        printf("%s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    } 

    if(first(MyToken, returnTypes)){
        if(!fc_returnTypes(MyToken, list)){
            return false;
        }
    }

    return true;
}
bool fc_global_scope(Token* MyToken,TokenList* list){                   //global_scope: global
    if(chackStr(MyToken,list,"global"))
    {
        printf("global_scope: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    
    
    return true;
}
bool fc_functionIden(Token* MyToken,TokenList* list){                   //functionIden: <functionIden>
    if (MyToken->type==Identifier){
        printf("functionIden: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    }
    return true;
}
bool fc_params(Token* MyToken,TokenList* list){                         //params: <param><nextParam>
    
    if(first(MyToken, param)){
        if(!fc_param(MyToken, list)){
            return false;
        }
    }
    else{
        return false;
    }

    if(first(MyToken, nextParam)){
        if(!fc_nextParam(MyToken, list)){
            return false;
        }
    }

    /*printf("params: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);*/
    return true;
}
bool fc_param(Token* MyToken,TokenList* list){                          //param: <identifier>:<type>
    if(MyToken->type==Identifier){
        printf("identifier: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }   
    else{
        return false;
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
        //return true;
    }
    else{
        return false;
    }

    return true;
}
bool fc_nextParam(Token* MyToken,TokenList* list){                      //nextparam: ,<param><nextparam>
    if (chackStr(MyToken, list, ",")){
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    }     

    if (first(MyToken, param)){
        if(!fc_param(MyToken, list)){

        }
    }
    else{
        return false;
    }

    if (first(MyToken, nextParam)){
        if(!fc_nextParam(MyToken, list)){
            return false;
        }
    }

    return true;
}
bool fc_returnTypes(Token* MyToken,TokenList* list){                      //returnTypes: :type<nextType>
    if (MyToken->type==Colon){
        printf("returnTypes start: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);      
    }
    else{
        return false;
    } 

    if (isTokenType(MyToken)){
        //printf("Type: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
    }
    else{
        return false;
    }

    if (first(MyToken, nextType)){
        if(!fc_nextType(MyToken, list)){
            return false;
        }
    }
    
    return true;
}
bool fc_nextType(Token* MyToken,TokenList* list){                            //nextType: ,Type<nextType>
    if (chackStr(MyToken, list, ",")){
        printf("String: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
        //return true;
    }
    else{
        return false;
    }

    if (isTokenType(MyToken)){
        printf("Type: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
        printf("Type: %s\n",MyToken->att);
    }
    else{
        return false;
    }
    
    if (first(MyToken, nextType)){
        printf("nextType: %s\n",MyToken->att);
        tokenScan(stdin, list, MyToken);
        return true;
        
    }

    return true;
}
bool fc_statement(Token* MyToken,TokenList* list){                              //statemnet: <<loop>||<condition>||<assigne>||<define>> <statment>
    if (first(MyToken, loop)){
        if(!fc_loop(MyToken, list)){
            return false;
        }
    }
    else if (first(MyToken, condition)){
        if(!fc_condition(MyToken, list)){
            return false;
        }
    }
    else if (first(MyToken, assigne)){
        if(!fc_assigne(MyToken, list)){
            return false;
        }
    }
    else if (first(MyToken, loop)){
        if(!fc_define(MyToken, list)){
            return false;
        }
    }
    else{
        return false;
    }

    if (first(MyToken, statement)){
        if (!fc_statement(MyToken, list)){
            return false;
        }    
    }    
    return true;
}
bool fc_loop(Token* MyToken,TokenList* list){
    printf("loop: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_condition(Token* MyToken,TokenList* list){
    printf("condition: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);
    return true;
    }
bool fc_assigne(Token* MyToken,TokenList* list){
    //printf("assigne: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);
    return true;
}
bool fc_define(Token* MyToken,TokenList* list){
    printf("define: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    if ((MyToken->type != Number) || (MyToken->type != Integer)){
        printf("StringCheck: %s\n",MyToken->att);
        if (strcmp(MyToken->att,checkType)==0){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    
    
    
}
/*
    je identifikator
*/
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
    else
    {
        return false;
    }
    
}