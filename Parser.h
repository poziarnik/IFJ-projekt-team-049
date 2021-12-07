#ifndef _parcer
#define _parcer
#include <stdio.h>
#include <stdlib.h>
#include "ParserDownUp.h"
#include "error.h"
#include "symtable.h"
#include "AST.h"
#include "generator.h"

#define PARC_TRUE 0
#define PARC_FALSE 2

#define RETURN_ON_ERROR(_function) \
    if ((status = _function(MyToken, list, mySymtable, abstractTree)) != PARC_TRUE) return status

#define RETURN_ON_ERROR_FCCALL(_withIDs) \
    if ((status = fc_functionCall(MyToken, list, mySymtable, abstractTree, _withIDs)) != PARC_TRUE) return status

#define SCAN_TOKEN \
    status = tokenScan(stdin, list, MyToken); \
    if (status==LEXICAL_ERROR) return LEXICAL_ERROR;
    // if (status==10) return 0;

/*status = tokenScan(stdin, list, MyToken); \
    if (status==LEXICAL_ERROR) return LEXICAL_ERROR; \
    if (status==10) return 0;*/
/////////////////////

/*typedef struct root{
    struct state **global_state;
}TRoot;

typedef struct state{
    union statement{
        struct function_tree *function;
        struct if_tree *if_loop; 
        struct while_tree *while_loop;
        //struct assign_tree *assignment;
        struct definition_tree *definiton;
        //struct functioncall_tree *functioncall;
    }TStatement;
}Tstate;

typedef struct function_tree{
    char *id;                       //token->data.string??
    char **parameter;               //token->data.string??
    char **return_type;             //token->data.string??
    struct state **statements;
}TFunction_tree;

typedef struct if_tree{
    Tree *expression;
    struct state **then_statement;
    struct state **else_statement;
}TIf_tree;

typedef struct while_tree{
    Tree *expression;
    struct state **do_statement;
}TWhile_tree;

/*typedef struct assign_tree{
    //TODO
}TAssign_tree;

typedef struct definition_tree{
   char *id;
   char **data_type;
   char **value;
}TDefinition_tree;

typedef struct functioncall{
    //TODO
}TFunctioncall;*/


//////////////////////////

// typedef struct st_program{
//     struct st_statment** blocks;
//     int nb_blocks; 
// }AT_program;

// typedef struct st_statement{     
    
//     union{
//         struct st_loop* loop;  
//         struct st_condition* condition;
//     }data;
                  
// }AT_statement;

// typedef struct st_loop{      

//     struct st_expression* expr;
//     struct st_statement** blocks;
//     int nb_blocks;
                  
// }AT_loop;

// typedef struct st_condition{        

//     struct st_expression* expr;
//     struct st_statement** blocks;
//     int nb_blocks;
// }AT_condition;

// typedef struct st_expression
// {
//     struct st_expression* expr;        //expession tree
//     struct st_statement** blocks;
//     int nb_blocks;

// }AT_expression;

// typedef struct st_define{       

//     struct st_expression* expr;
//     struct st_statement** blocks;
//     int nb_blocks;
        
// }AT_define;

// typedef struct st_assigne{        

//     struct st_expression* expr;
//     struct st_statement** blocks;
//     int nb_blocks;
// }AT_assigne;
//////////////////////////////////////////////////

typedef enum{
    program,
    prolog,
    code,
    functionDec,
    statement,
    global_scope,   //function rozklad
    function_iden,
    params,
    param,
    nextParam,
    returnTypes,
    type,
    nextType,
    condition,      //statment rozklad
    loop,
    assigneOrFunctioCall,
    define,
    expression,
    nextExpression,
    varlist,
    var,
    nextVar,
    initialize,
    elseCondition,
    functionCall,
    FCallparams,
    FCallparam,
    FCallnextParam,
    FCreturn,
    returnParams,
    returnParam,
    returnNextParam,
    statementOutOfFc
}NonTerminal;

int Parse(TokenList* list, ASTtree* abstractTree, symtable* mySymtable);
bool first(Token* MyToken, NonTerminal MyNonTerminal);
int fc_program(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                       //program: <prolog><code>
int fc_code(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                          //code: <functionDec><code><statement>
int fc_statementOutOfFc(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree);              //statementOutOfFc: <functionDec>||<functionCall>(bez ids) <statementOutOfFc>
int fc_functionDec(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                    //functionDec: <global_scope>function<function_iden>(<params><returntypes>)<statement>end
int fc_global_scope(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                   //global_scope: global
int fc_functionIden(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                   //functionIden: <functionIden>
int fc_params(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                         //params: <param><nextParam>
int fc_returnTypes(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                    //returnTypes: :type<nextType>
int fc_statement(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                      //statemnet: <<loop>||<condition>||<assigne>||<define>> <statment>
int fc_param(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                          //param: <identifier>:<type>
int fc_nextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                      //nextparam: ,<param><nextparam>
int fc_nextType(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                       //nextType: ,Type<nextType>
int fc_loop(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                           //loop: while<expression>do<statement>end
int fc_condition(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                      //condition: if<expresion>then<statement><elseCondition>end
int fc_elseCondition(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                  //elseCondition: else<statement>
int fc_assigne(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                        //assigne: <var><nextVar>=<expresion><nextExpresion>||<fcCall>
int fc_define(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                         //define: local|identifier:type<inicialize>
int fc_expression(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                     //expression: identifier||number||integer||string||sizeof||L_bracet
int fc_nextExpression(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                 //nextExpression: ,<expresion><nextExpression>
int fc_var(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                            //var: identifier
int fc_nextVar(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                        //nextVar: ,<var><nextVar>
int fc_initialize(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                     //initialize: =<expresion>||<functionCall>
int fc_functionCall(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree,bool withIDs);      //functionCall: identifier(<FCparams>)
int fc_prolog(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                         //prolog: requier ifj21
int fc_FCallparams(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                    //FCallparams: <FCallparam><FCallnextParam>
int fc_FCallparam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                     //FCallparam: <expression>
int fc_FCallnextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                 //FCallnextParam: ,<FCallparam><FCallnextparam>
int fc_FCreturn(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                       //FCreturn: return <FCparams>
int fc_returnParams(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                   //returnParams: <returnParam><returnNextParam>
int fc_returnParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                    //returnParam: <expression>
int fc_returnNextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);                //returnNextParam: ,<returnParam><returnNextParam>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parcerPrint(char* state ,Token* MyToken ,bool on);
bool chackStr(Token* MyToken, TokenList* list, char* checkType);

/**
 * @brief Porovna typ tokenu so zadanym typom chacktype, ak su zhodne naskenuje novy token ak nie vrati PARC_FALSE 
 * 
 * @param MyToken 
 * @param list 
 * @param checkType 
 * @return int 
 */
int chackType(Token* MyToken, TokenList* list, Token_type checkType);

/**
 * @brief Porovna string ulozeny v tokene a parameter str 
 * 
 * @param MyToken 
 * @param Str 
 * @return true 
 * @return false 
 */
bool compareTokenStr(Token* MyToken, char* Str);

/**
 * @brief kontroluje ci je token typu integer string alebo number
 * 
 * @param MyToken 
 * @return true 
 * @return false 
 */
bool isTokenDataType(Token* MyToken);
int global_level_root();
void printGlobalTree(symtable* mySymtable);
void printGlobalTree(symtable* mySymtable);

#endif
