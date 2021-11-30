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
    ASTdefinition,
    ASTassigne,
    ASTfunctionCall
}statementType;

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
    char *id;                       //token->data.string??
    char **parameter;               //token->data.string??
    char **return_type;             //token->data.string??
    struct state **statements;
    int* nbStatements;
}TFunction_tree;

typedef struct if_tree{
    Tree *expression;
    struct state **then_statement;
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
    char **ID;
    Tree **expressions;
}TAssign_tree;

typedef struct definition_tree{
   char *id;
   char **data_type;
   char **value;
}TDefinition_tree;

typedef struct aststack{
    struct ast_stackElement* head;
}ASTstack;

typedef struct ast_stackElement{
    struct state *statement;
    struct ast_stackElement* next; 
}ASTstackElement;
typedef struct functioncall_tree{
    char **ID;  //podla mna to musi byt pole, lebo ID moze byt viac
    char *functionName;
    char **parameters; //rovnako ako pri ID, moze byt viac vstupnych parametrov
}TFunctioncall_tree;

int ASTStackPush(ASTstack* myStack, Tstate* newStatement);
int ASTaddFCToTree(ASTstack* myStack);
int ASTaddToStatements(Tstate*** statements, int* nbStatements, Tstate* newStatement);
Tstate** ASTcreateStatements(int* nbStatements);
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