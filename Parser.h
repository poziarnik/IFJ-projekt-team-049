#include <stdio.h>
#include <stdlib.h>
#include "ParserDownUp.h"

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





}NonTerminal;

int Parse(TokenList* list);
bool first(Token* MyToken, NonTerminal MyNonTerminal);
bool fc_program(Token* MyToken, TokenList* list);
bool fc_code(Token* MyToken, TokenList* list);
bool fc_functionDec(Token* MyToken,TokenList* list);
bool fc_global_scope(Token* MyToken,TokenList* list);
bool fc_functionIden(Token* MyToken,TokenList* list);
bool fc_params(Token* MyToken,TokenList* list);
bool fc_returnTypes(Token* MyToken,TokenList* list);
bool fc_statement(Token* MyToken,TokenList* list);
bool chackStr(Token* MyToken, TokenList* list, char* checkType);
bool chackType(Token* MyToken, TokenList* list, Token_type checkType);