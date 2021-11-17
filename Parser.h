#include <stdio.h>
#include <stdlib.h>
#include "ParserDownUp.h"
#include "error.h"

#define PARC_TRUE 0
#define PARC_FALSE -1

#define RETURN_ON_ERROR(_function) \
    if ((status = _function(MyToken, list)) != PARC_TRUE) return status

#define SCAN_TOKEN \
    status = tokenScan(stdin, list, MyToken); \
    if (status==1) return 1; \
    if (status==10) return 10

typedef struct st_program{
    struct st_statment** blocks;
    int nb_blocks; 
}AT_program;

typedef struct st_statement{     
    
    union{
        struct st_loop* loop;  
        struct st_condition* condition;
    }data;
                  
}AT_statement;

typedef struct st_loop{      

    struct st_expression* expr;
    struct st_statement** blocks;
    int nb_blocks;
                  
}AT_loop;

typedef struct st_condition{        

    struct st_expression* expr;
    struct st_statement** blocks;
    int nb_blocks;
}AT_condition;

typedef struct st_expression
{
    struct st_expression* expr;        //expession tree
    struct st_statement** blocks;
    int nb_blocks;

}AT_expression;

typedef struct st_define{       

    struct st_expression* expr;
    struct st_statement** blocks;
    int nb_blocks;
        
}AT_define;

typedef struct st_assigne{        

    struct st_expression* expr;
    struct st_statement** blocks;
    int nb_blocks;
}AT_assigne;



typedef enum{
    program,
    prolog,
    code,
    functionDec,
    statement,
    global_scope,   //function rozklad
    function_iden,
    params,
    returnTypes,
    param,
    nextParam,
    type,
    nextType,
    condition,      //statment rozklad
    loop,
    assigne,
    define,
    expression,
    nextExpression,
    varlist,
    var,
    nextVar,
    initialize,
    elseCondition,
    functionCall




}NonTerminal;

int Parse(TokenList* list);
bool first(Token* MyToken, NonTerminal MyNonTerminal);
int fc_program(Token* MyToken, TokenList* list);
int fc_code(Token* MyToken, TokenList* list);
int fc_functionDec(Token* MyToken,TokenList* list);
int fc_global_scope(Token* MyToken,TokenList* list);
int fc_functionIden(Token* MyToken,TokenList* list);
int fc_params(Token* MyToken,TokenList* list);
int fc_returnTypes(Token* MyToken,TokenList* list);
int fc_statement(Token* MyToken,TokenList* list);
bool chackStr(Token* MyToken, TokenList* list, char* checkType);
int chackType(Token* MyToken, TokenList* list, Token_type checkType);
int fc_param(Token* MyToken,TokenList* list);
int fc_nextParam(Token* MyToken,TokenList* list);
bool isTokenType(Token* MyToken);
int fc_nextType(Token* MyToken,TokenList* list);
int fc_loop(Token* MyToken,TokenList* list);
int fc_condition(Token* MyToken,TokenList* list);
int fc_assigne(Token* MyToken,TokenList* list);
int fc_define(Token* MyToken,TokenList* list);
bool compareTokenStr(Token* MyToken, char* Str);
int fc_expression(Token* MyToken,TokenList* list);
int fc_nextExpression(Token* MyToken,TokenList* list);
int fc_elseCondition(Token* MyToken,TokenList* list);
int fc_var(Token* MyToken,TokenList* list);
int fc_nextVar(Token* MyToken,TokenList* list);
int fc_initialize(Token* MyToken,TokenList* list);
int fc_functionCall(Token* MyToken,TokenList* list);
int fc_prolog(Token* MyToken,TokenList* list);
void parcerPrint(char* state ,Token* MyToken ,bool on);