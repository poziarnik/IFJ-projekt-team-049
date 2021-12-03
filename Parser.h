#ifndef _parcer
#define _parcer
#include <stdio.h>
#include <stdlib.h>
#include "ParserDownUp.h"
#include "error.h"
#include "symtable.h"
#include "AST.h"

#define PARC_TRUE 0
#define PARC_FALSE 2

#define RETURN_ON_ERROR(_function) \
    if ((status = _function(MyToken, list, mySymtable, abstractTree)) != PARC_TRUE) return status

#define RETURN_ON_ERROR_FCCALL(_withIDs) \
    if ((status = fc_functionCall(MyToken, list, mySymtable, abstractTree, _withIDs)) != PARC_TRUE) return status

#define SCAN_TOKEN \
    status = tokenScan(stdin, list, MyToken); \
    if (status==LEXICAL_ERROR) return LEXICAL_ERROR; \
    if (status==10) return 0;

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
}NonTerminal;

int Parse(TokenList* list, ASTtree* abstractTree);
bool first(Token* MyToken, NonTerminal MyNonTerminal);
int fc_program(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_code(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_functionDec(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_global_scope(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_functionIden(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_params(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_returnTypes(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_statement(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_param(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_nextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_nextType(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_loop(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_condition(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_assigne(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_define(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_expression(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_nextExpression(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_elseCondition(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_var(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_nextVar(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_initialize(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_functionCall(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree,bool withIDs);
int fc_prolog(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
void parcerPrint(char* state ,Token* MyToken ,bool on);
bool chackStr(Token* MyToken, TokenList* list, char* checkType);
int fc_FCallparams(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_FCallparam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_FCallnextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);
int fc_FCreturn(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
