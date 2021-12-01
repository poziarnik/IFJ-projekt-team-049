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
    ASTfunctionCall
}statementType;

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
        struct global* root;
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
    Tree *expression;
    struct state **if_statement;
    int* nbThenStatements;
    struct state **else_statement;
    int* nbElseStatements;
}TIf_tree;


typedef struct while_tree{
    Tree *expression;
    struct state **do_statement;
    int* nbStatements;
}TWhile_tree;

typedef struct assign_tree{
    Token **ID;
    int* nbID;
    Tree **expressions;
    int* nbexpressions;
}TAssign_tree;

typedef struct definition_tree{
   Token *id;
   Token *data_type;
   Tree *expression;
}TDefinition_tree;

typedef struct aststack{
    struct ast_stackElement* head;
}ASTstack;

typedef struct ast_stackElement{
    struct state *statement;
    struct ast_stackElement* next; 
}ASTstackElement;

typedef struct functioncall_tree{
    Token **ID;  //podla mna to musi byt pole, lebo ID moze byt viac
    int* nbID;
    Token *functionName;
    Token **parameters; //rovnako ako pri ID, moze byt viac vstupnych parametrov
    int* nbParameters;
}TFunctioncall_tree;

//!!!!! za kazdym define assigne FCcall musi ist po naplneni parametrov end
ASTtree* ASTtreeCreate();
int ASTStackPush(ASTstack* myStack, Tstate* newStatement);
int ASTaddFCToTree(ASTstack* myStack);
int ASTaddCycleToTree(ASTstack* myStack);
int ASTaddDefineToTree(ASTstack* myStack);
int ASTaddAssigmentToTree(ASTstack* myStack);
int ASTaddFCcallToTree(ASTstack* myStack);

Tstate** ASTcreateStatements(int* nbStatements);
int ASTaddToStatements(Tstate*** statements, int* nbStatements, Tstate* newStatement);
Tree** ASTcreateExpressions(int* nbExpressions);
int ASTaddToExpressions(Tree*** espressions, int* nbExpressions, Tree* newExpression);
Tstate*** ASTreturnFastST(ASTstack* myStack);
int* ASTreturnFastNB(ASTstack* myStack);
void ASTendStatement(ASTstack *myStack);
int ASTnewElementInit(Tstate* newElement, statementType Type);
//void ASTprintTree(TRoot* tree);
void ASTprintStatement(Tstate* statement);
void ASTstackInit(ASTstack* myStack);
Tstate* ASTcreateLeaf(statementType type);
void ASTprintStack(ASTstack* myStack);

#endif 