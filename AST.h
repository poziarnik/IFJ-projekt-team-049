/**
 * Projekt : Implementace prekladace imperativniho jazyka IFJ21
 * @file AST.h
 * @author Juraj Hatala (xhatal01)
 * @brief hlavickovy subor abstraktneho stromu
 *  
 */

#ifndef _AST
#define _AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Scanner.h"
#include "MyStackTree.h"

typedef enum{
    ASTglobal,
    ASTfunction,
    ASTcondition,
    ASTcycle,
    ASTdefine,
    ASTassigne,
    ASTfunctionCall,
    ASTreturn
}statementType;

typedef enum{
    functionParams,
    functionID,
    functionReturnTypes,
    assigneIDs,
    definitionID,
    definitionDataType,
    functionCallIDs,
    functionCallName,
    functionCallParams
}saveType;

typedef enum{
    readi,
    reads,
    readn,
    write,
    tointeger,
    ord,
    substr,
    chr,
    empty
}inbuild;

typedef enum{
    IfStatement,
    ElseStatement
}ifOrElse;

typedef enum{
    Empty,
    Expression,
    FCcall
}defineState;

typedef struct AST{
    struct state* tree;
    struct aststack* ASTStack;
    
}ASTtree;
/*typedef struct root{
    struct state **global_state;
}TRoot;*/

typedef struct global{
    struct state **statements;
    int* nbStatements;
    inbuild UsedInBuild[8];
}root;

typedef struct state{
    statementType type;
    union statement{
        struct function_tree *function;
        struct if_tree *if_loop; 
        struct while_tree *while_loop;
        struct assign_tree *assignment;
        struct definition_tree *definiton;
        struct functioncall_tree *functioncall;
        struct global *root;
        struct returnTree *FCreturn;
    }TStatement;
}Tstate;


typedef struct function_tree{
   Token *id;                       //token->data.string??
    Token **parameters;               //token->data.string??
    int* nbParameters;
    Token **returnTypes;             //token->data.string??
    int* nbReturntypes;
    struct state **statements;
    int* nbStatements;
}TFunction_tree;

typedef struct if_tree{
    bool* hasElse;
    Tree *expression;
    struct state **if_statements;
    int* nbIfStatements;
    struct state **else_statements;
    int* nbElseStatements;
}TIf_tree;


typedef struct while_tree{
    Tree *expression;
    struct state **do_statement;
    int* nbStatements;
}TWhile_tree;

typedef struct assign_tree{
    Token **IDs;
    int* nbID;
    Tree **expressions;
    int* nbexpressions;
}TAssign_tree;

typedef struct definition_tree{
    defineState* state;
    Token *id;
    Token *data_type;
    union exfc {
        Tree *expression;
        struct state* FCcall;
    } ExFc;
} TDefinition_tree;

typedef struct aststack{
    struct ast_stackElement* head;
}ASTstack;

typedef struct ast_stackElement{
    struct state *statement;
    struct ast_stackElement* next; 
}ASTstackElement;

/**
 * @brief struktura leafu FCcall k stromu AST  
 * 
 */
typedef struct functioncall_tree{
    Token **IDs;  //podla mna to musi byt pole, lebo ID moze byt viac
    int* nbID;
    Token *functionName;
    Tree **parameters; //rovnako ako pri ID, moze byt viac vstupnych parametrov
    int* nbParameters;
}TFunctioncall_tree;

typedef struct returnTree{
    Tree **expressions;
    int* nbexpressions;
}Treturn_tree;


//!!!!! za kazdym define assigne FCcall musi ist po naplneni parametrov end

ASTtree* ASTtreeCreate();
int ASTStackPush(ASTstack* myStack, Tstate* newStatement);
int ASTaddFCToTree(ASTstack* myStack);

/**
 * @brief prida do AST cycle uzol a vlozi ho na vrch zasobniku
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddCycleToTree(ASTstack* myStack);

/**
 * @brief prida do AST define uzol a vlozi ho na vrch zasobniku
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddDefineToTree(ASTstack* myStack);

/**
 * @brief prida do AST assigment uzol a vlozi ho na vrch zasobniku
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddAssigmentToTree(ASTstack* myStack);

/**
 * @brief prida do AST functioCall uzol a vlozi ho na vrch zasobniku
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddFCcallToTree(ASTstack* myStack);

/**
 * @brief prida do AST condition uzol a vlozi ho na vrch zasobniku
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddConditionToTree(ASTstack* myStack);

/**
 * @brief prida do AST return uzol a vlozi ho na vrch zasobniku
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddReturnToTree(ASTstack* myStack);

/**
 * @brief ak je na vrchu zasobnika uzol condition tak zavola alokovanie miesta pre if statementy a nastavy hasElse na true
 * 
 * @param myStack 
 * @return int 
 */
int ASTaddElseToCondition(ASTstack* myStack);

/**
 * @brief alokuje v uzli pre condition dalsie miesto pre else statements a ich pocet
 * 
 * @param myStack 
 * @return int 
 */
int ASTallocateSpaceForElse(ASTstack* myStack);

/**
 * @brief Vyuziva sa pri urcovani ci ide o fccall alebo assigment, vytvori novy FCcall odstrani assigment a vsetky jeho ids vlozi do fccall ids
 * 
 */
int ASTswitchAssigneFCcall(ASTstack* myStack);

/**
 * @brief znizi pocet statementov v nadradenom statemente takze najblizsie zapisovany leaf sa zapise na jeho miesto
 * 
 * @param myStack 
 */
void ASTdeleteLastFromTree(ASTstack* myStack);

/**
 * @brief allokuje miesto pre statementy(pouziva sa na alokovanie miesta v uzle stromu)
 * 
 * @param nbStatements 
 * @return Tstate** 
 */
Tstate** ASTcreateStatements(int* nbStatements);

/**
 * @brief prida do pola statementov zadany newStatement, ak pre neho nie je miesto alokuje dalsie miesto
 * 
 * @param statements 
 * @param nbStatements 
 * @param newStatement 
 * @return int 
 */
int ASTaddToStatements(Tstate*** statements, int* nbStatements, Tstate* newStatement);

/**
 * @brief allokuje miesto pre vyrazi(pouziva sa na alokovanie miesta v uzle stromu)
 * 
 * @param nbExpressions 
 * @return Tree** 
 */
Tree** ASTcreateExpressions(int* nbExpressions);

/**
 * @brief prida do pola vyrazov zadany newExpression, ak pre neho nie je miesto alokuje dalsie miesto
 * 
 * @param espressions 
 * @param nbExpressions 
 * @param newExpression 
 * @return int 
 */
int ASTaddToExpressions(Tree*** espressions, int* nbExpressions, Tree* newExpression);

/**
 * @brief vrati statement z vrchu stacku(pouzite len na skratenie zapisu(makro by bolo sikovnejsie :( )))
 * 
 * @param myStack 
 * @return Tstate*** 
 */
Tstate*** ASTreturnFastST(ASTstack* myStack);

/**
 * @brief vrati pocet statementov zo statementu na vrchu zasobnika
 * 
 * @param myStack 
 * @return int* 
 */
int* ASTreturnFastNB(ASTstack* myStack);

/**
 * @brief prida zadany Token do zadaneho pola tokenov
 * 
 * @param array 
 * @param nbTokens 
 * @param newToken 
 * @return int 
 */
Token** ASTcreateTokenArray(int* nbTokens);

/**
 * @brief Prida newToken do pola tokenov ak je pole male zvacsi ho
 * 
 * @param array 
 * @param nbTokens 
 * @param newToken 
 * @return int 
 */
int ASTaddToTokenArray(Token*** array, int* nbTokens, Token* newToken);

/**
 * @brief ukonci sucasne upravovany statement na vrchu staku("stackPop"). Musi nasledovat za kazdym assigment a define a vsetkym proste
 * 
 * @param myStack 
 */
void ASTendStatement(ASTstack *myStack);

/**
 * @brief inicializuje zasobnik
 * 
 * @param myStack 
 */
void ASTstackInit(ASTstack* myStack);

/**
 * @brief vytvori prazdny list zadaneho typu Tstate v AST a alokuje vstky jeho casti
 * 
 * @param type 
 * @return Tstate* 
 */
Tstate* ASTcreateLeaf(statementType type);

/**
 * @brief ulozi Token do AST vyber si z enum savetype co chces ukladat(uklada tokeny a polia tokenov) vracanie INTEGRALERROR
 * 
 * @param myStack 
 * @param myToken 
 * @param type 
 * @return int 
 */
int ASTsaveToken(ASTstack* myStack, Token* myToken, saveType type);

/**
 * @brief vrati cestu stackom k velkosti pola tokenov v danom type unie Tstate(len na zkratenie zapisu) 
 * 
 * @param myStack 
 * @param type 
 * @return Token*** 
 */
int* ASTreturnFastArrayNB(ASTstack* myStack, saveType type);

/**
 * @brief vrati cestu stackom k polu tokenov v danom type unie Tstate(len na zkratenie zapisu) 
 * 
 * @param myStack 
 * @param type 
 * @return Token*** 
 */
Token*** ASTreturnFastArray(ASTstack* myStack, saveType type);

/**
 * @brief vypis obsah AST stromu 
 * 
 * 
 * @param statement 
 */
void ASTprintStatement(Tstate* statement);

/**
 * @brief vypis obsah stacku
 * 
 * @param myStack 
 */
void ASTprintStack(ASTstack* myStack);

/**
 * @brief zapise do pola enumov v AST ze zadana inbuild funkcia bola v programe pouzita 
 * 
 */
void ASTinBuildUsed(ASTtree* tree, inbuild FC);

/**
 * @brief inicializuje pole pouzitych funkcii na empty pri vytvoreni AST
 * 
 * @param array 
 */
void ASTinBuildArrayInit(inbuild* array);

/**
 * @brief Print expression stromu
 * 
 * @param exprtree -strom
 */
void printExpressionTree(Tree *exprtree);

/**
 * @brief vypise pouzite inBuild funkcie (enum)
 * 
 * @param tree 
 */
void ASTprintInBuild(ASTtree* tree);

/**
 * @brief kontroluje ci bola zadana inbuild funkcia v programe pouzita
 * 
 * @param tree 
 * @param FC 
 * @return true 
 * @return false 
 */
bool ASTisInBuildUsed(ASTtree* tree, inbuild FC);

#endif 