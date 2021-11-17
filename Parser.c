#include "Parser.h"

#define PRINT_ON true //ak chces printovat priebeh nastav true ak nie nastav false
/*global function factorial ( n : integer, a : number) : integer , number 
while e do end 21*/
//bacha segfault
int Parse(TokenList* list){
    int status;
    Token* MyToken=(Token*)malloc(sizeof(Token));
    tokenScan(stdin, list, MyToken);
    RETURN_ON_ERROR(fc_program);
    
    return PARC_TRUE;
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
        else if(MyToken->type==Keyword){
            if(strcmp(MyToken->data.string, "function")==0){
                return true;
            }
        }
    }
    else if(MyNonTerminal==global_scope){
        if(strcmp(MyToken->data.string, "global")==0){
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
            if (strcmp(MyToken->data.string,"if")==0){
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
            if (strcmp(MyToken->data.string,"while")==0){
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
            if (strcmp(MyToken->data.string,"local")==0){
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
        if (first(MyToken,var)){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==varlist){
        if (first(MyToken,var)){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==var){
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
        
    }
    else if (MyNonTerminal == nextVar){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==expression)
    {
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal == nextExpression){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==functionCall)
    {
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal == elseCondition)
    {
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"else")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == prolog)
    {
        if(MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"require")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == initialize)
    {
        if (MyToken->type==Assign){
            return true;
        }
        else return false;
    }
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!dorobit nejake first

    return false;
}
//ak chyba alebo koniec return ak nie tak nereturnuj nic




    
    


int fc_program(Token* MyToken, TokenList* list){                  //program: <prolog><code>
    int status;
    if(first(MyToken, prolog)){
        RETURN_ON_ERROR(fc_prolog);
    }

    if(first(MyToken, code)){
        RETURN_ON_ERROR(fc_code);
    }
    else return PARC_FALSE;
    
    
    return PARC_TRUE;
}
int fc_code(Token* MyToken, TokenList* list){                     //code: <functionDec><code><statement>
    int status;
    if (first(MyToken, functionDec)){
        RETURN_ON_ERROR(fc_functionDec);
    }
    else{
        return PARC_FALSE;
    }
    
    if (first(MyToken, code)){
        RETURN_ON_ERROR(fc_code);
    }
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement); 
    }
    
    return PARC_TRUE;
}
int fc_functionDec(Token* MyToken,TokenList* list){              //functionDec: <global_scope>function<function_iden>(<params><returntypes>)<statement>end
    int status;
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
        RETURN_ON_ERROR(fc_global_scope);
    }

    if (chackStr(MyToken, list, "function")){
        printf("String: %s\n",MyToken->data.string);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if(first(MyToken, function_iden)){
        RETURN_ON_ERROR(fc_functionIden);
    }
    else return PARC_FALSE;

    if (MyToken->type==L_bracket){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, params)){
       RETURN_ON_ERROR(fc_params);
    }

    if (MyToken->type==R_bracket){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
      
    if(first(MyToken, returnTypes)){
        RETURN_ON_ERROR(fc_returnTypes);
    }
    
    if(first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
    
    if (chackStr(MyToken, list, "end")){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    return PARC_TRUE;
}
int fc_global_scope(Token* MyToken,TokenList* list){                   //global_scope: global
    int status;
    if(chackStr(MyToken,list,"global"))
    {
        parcerPrint("global" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    
    
    return PARC_TRUE;
}
int fc_functionIden(Token* MyToken,TokenList* list){                   //functionIden: <functionIden>
    int status;
    if (MyToken->type==Identifier){
        parcerPrint("function_Iden" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }
    return PARC_TRUE;
}
int fc_params(Token* MyToken,TokenList* list){                         //params: <param><nextParam>
    int status;
    if(first(MyToken, param)){
        RETURN_ON_ERROR(fc_param);
    }
    else{
        return PARC_FALSE;
    }

    if(first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_nextParam);
    }

    /*printf("params: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);*/
    return PARC_TRUE;
}
int fc_param(Token* MyToken,TokenList* list){                          //param: <identifier>:<type>
    int status;
    if(MyToken->type==Identifier){
        parcerPrint("identifier" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }   
    else{
        return PARC_FALSE;
    }

    if (chackStr(MyToken, list, ":")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    } 

    if(isTokenType(MyToken)){
        int status;
        parcerPrint("param" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
        //return true;
    }
    else{
        return PARC_FALSE;
    }

    return PARC_TRUE;
}
int fc_nextParam(Token* MyToken,TokenList* list){                      //nextparam: ,<param><nextparam>
    int status;
    if (chackStr(MyToken, list, ",")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }     

    if (first(MyToken, param)){
        RETURN_ON_ERROR(fc_param);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_nextParam);
    }

    return PARC_TRUE;
}
int fc_returnTypes(Token* MyToken,TokenList* list){                      //returnTypes: :type<nextType>
    int status;
    if (MyToken->type==Colon){
        parcerPrint("return_types start" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;     
    }
    else{
        return PARC_FALSE;
    } 

    if (isTokenType(MyToken)){
        //printf("Type: %s\n",MyToken->att);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextType)){
        RETURN_ON_ERROR(fc_nextType);
    }
    
    return PARC_TRUE;
}
int fc_nextType(Token* MyToken,TokenList* list){                            //nextType: ,Type<nextType>
    int status;
    if (chackStr(MyToken, list, ",")){
        parcerPrint("next_type" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (isTokenType(MyToken)){
        parcerPrint("type" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    
    }
    if (first(MyToken, nextType)){
        RETURN_ON_ERROR(fc_nextType);
    }

    return PARC_TRUE;
}
int fc_statement(Token* MyToken,TokenList* list){                              //statemnet: <<loop>||<condition>||<assigne>||<define>> <statment>
    
    int status;
    if (first(MyToken, loop)){
        RETURN_ON_ERROR(fc_loop);
    }
    else if (first(MyToken, condition)){
        RETURN_ON_ERROR(fc_condition);
    }
    else if (first(MyToken, assigne)){
        RETURN_ON_ERROR(fc_assigne);
    }
    else if (first(MyToken, define)){
        RETURN_ON_ERROR(fc_define);
    }
    else if (first(MyToken, functionCall)){
        RETURN_ON_ERROR(fc_functionCall);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);    
    }    
    return PARC_TRUE;
}
int fc_loop(Token* MyToken,TokenList* list){                                    //loop: while<expression>do<statement>end
    int status;
    if (chackStr(MyToken, list, "while")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, "do")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }

    if (chackStr(MyToken, list, "end")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_condition(Token* MyToken,TokenList* list){                               //condition: if<expresion>then<statement><elseCondition>end
    int status;
    if (chackStr(MyToken, list, "if")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, "then")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }

    if(first(MyToken,elseCondition)){
        RETURN_ON_ERROR(fc_elseCondition);
    }

    if (chackStr(MyToken, list, "end")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_elseCondition(Token* MyToken,TokenList* list){                               //else<statement>
    int status;
    if (chackStr(MyToken, list, "else")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }

    return PARC_TRUE;
}
    
int fc_assigne(Token* MyToken,TokenList* list){                                      //<var><nextVar>=<expresion><nextExpresion>     or varlist=expresionlist
    int status;
    if (first(MyToken, var)){
        RETURN_ON_ERROR(fc_var);
    }
    else return PARC_FALSE;

    if (first(MyToken, nextVar)){
        RETURN_ON_ERROR(fc_nextVar);
    }
    
    if (MyToken->type==Assign){
        parcerPrint("assign" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;    
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;

    if (first(MyToken, nextExpression)){
        RETURN_ON_ERROR(fc_nextExpression);
    }
    
    return PARC_TRUE;
}
int fc_var(Token* MyToken,TokenList* list){                                         //identifier
    int status;
    if(MyToken->type==Identifier){
        parcerPrint("var" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
int fc_nextVar(Token* MyToken,TokenList* list){                                     //,<var><nextVar>
    int status;
    if (chackStr(MyToken, list, ",")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,var)){
        RETURN_ON_ERROR(fc_var);
    }
    else return PARC_FALSE;
    
    if (first(MyToken,nextVar)){
        RETURN_ON_ERROR(fc_nextVar);
    }
    
    return PARC_TRUE;
}
int fc_expression(Token* MyToken,TokenList* list){                                  //Martin Huba
    int status;
    parcerPrint("expression" ,MyToken ,PRINT_ON);
    SCAN_TOKEN;
    return PARC_TRUE;
}
int fc_nextExpression(Token* MyToken,TokenList* list){                              //,<expresion><nextExpression>
    int status;
    if (chackStr(MyToken, list, ",")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;

    if (first(MyToken,nextExpression)){
        RETURN_ON_ERROR(fc_nextExpression);
    }
    
    return PARC_TRUE;
}
int fc_define(Token* MyToken,TokenList* list){                                        //define: local|identifier:type<inicialize>
    int status;
    
    if (chackStr(MyToken, list, "local")){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    

    if (MyToken->type==Identifier){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, ":")){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }

    if(isTokenType(MyToken)){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,initialize)){
        RETURN_ON_ERROR(fc_initialize);
    }
    
    return PARC_TRUE;
}
int fc_functionCall(Token* MyToken,TokenList* list){                                 //functionCall: identifier(<params>)
    int status;                                                                      //zatial nie je pouzite(po implementacii symtable pridat do assigne a do define)
    if (MyToken->type==Identifier){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }

    if (chackStr(MyToken, list, "(")){
        
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,params)){
        RETURN_ON_ERROR(fc_params);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, ")")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
//dorobit function call !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int fc_initialize(Token* MyToken,TokenList* list){                                  //initialize: =<expresion>||<functionCall>
    int status;
    if (chackStr(MyToken, list, "=")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){                                                //!!!!!or functionCall
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    return PARC_TRUE;
}

int fc_prolog(Token* MyToken,TokenList* list){
    int status;
    if (MyToken->type==Keyword){
        if (chackStr(MyToken, list, "require")){
            parcerPrint("Prolog" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    if (MyToken->type==String){
        if (chackStr(MyToken, list, "ifj21")){
            parcerPrint("Prolog" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chackType(Token* MyToken, TokenList* list, Token_type checkType){    
    if (MyToken->type==checkType){
        printf("TypeCheck: %d\n",MyToken->type);
        int status;
        SCAN_TOKEN;
        return PARC_TRUE;
    }
    else{
        return PARC_FALSE;
    }
}

bool compareTokenStr(Token* MyToken, char* Str){
    if((MyToken->type != Number) || (MyToken->type != Integer)){
        //printf("kokot %s %s\n", MyToken->data.string, Str);
        if(strcmp(MyToken->data.string, Str)==0){
            //printf("kokot %s %s\n", MyToken->data.string, Str);
            return true;
        }
    }
    return false;
}
bool chackStr(Token* MyToken, TokenList* list, char* Str){
    if ((MyToken->type != Number) || (MyToken->type != Integer)){
        
        if (compareTokenStr(MyToken, Str)){
            //printf("StringCheck: %s\n",MyToken->data.string);
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
    if(compareTokenStr(MyToken, "integer")){
        return true;
    }
    else if(compareTokenStr(MyToken, "number")){
        return true;
    }
    else if(compareTokenStr(MyToken, "string")){
        return true;
    }
    else
    {
        return false;
    }
}
void parcerPrint(char* state ,Token* MyToken ,bool on){
    if (on){
        if ( MyToken->type==Integer){
            printf("%s: %d\n",state,MyToken->data.integer);
        }
        else if (MyToken->type==Number){
            printf("%s: %f\n",state,MyToken->data.number);
        }
        else{
            if (strcmp(state,"loop")==0)
            {
                printf("\033[1;33m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"condition")==0){
                printf("\033[0;32m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"assign")==0){
                printf("\033[0;31m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"define")==0){
                printf("\033[0;34m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else
            {
                printf("%s: %s\n",state,MyToken->data.string);
            }
        }
    }
}
    

