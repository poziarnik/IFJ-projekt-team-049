#include <stdio.h>
#include <stdlib.h>
#include "ParserDownUp.h"

typedef enum{
    program,
    prolog,
    code,
    finctionDec,
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
bool First(Token* MyToken, NonTerminal MyNonTerminal);