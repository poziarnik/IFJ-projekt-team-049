
/**
 *
 * @file symtable.h
 * @author Daniel Zalezak
 * @brief Header of symtable
 * @date 
 *
 */


#ifndef symtable_h
#define symtable_h
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int varType;
}tData;

typedef struct tableItem {
    char* key;
    tData* data;
    struct tableItem *lptr;
    struct tableItem *rptr;
    struct sym_treeRoot *subtree;    
}TreeItem;

typedef struct sym_stackElement{
    
    struct sym_stackElement *next;
    struct sym_treeRoot *root;
}SymStackElement;

typedef struct sym_treeRoot{
    struct tableItem *tree;
}SymTreeRoot;

typedef struct sym_stack{
    struct sym_stackElement* head;
}SymStack;

typedef struct symtable{
    TreeItem *sym_globalTree;
    SymTreeRoot *sym_subTree;
    SymStack *sym_stack;
}symtable;


// typedef struct tSymbolTable {
//     struct tableItem *root;
// } tSymbolTable;

//void tableInit(tSymbolTable *T);
void bst_insert(TreeItem **tree, char* key, TreeItem *new);
void TreeItemInit(TreeItem *treeitem);
bool sym_search(TreeItem *tree, char* key);
void symStackPop(SymStack *myStack);  
int symStackPush(SymStack* myStack, SymTreeRoot* tree);
void symStackTop(SymStack* myStack, SymTreeRoot* tree);
void symStackInit(SymStack* myStack);
TreeItem* treeCreate();
void sym_treeInit(TreeItem *newTree);
int sym_saveFun(TreeItem **sym_globalTree, SymTreeRoot **sym_subTree,SymStack* myStack, char* key);
bool isFunDeclared(char* key, TreeItem* globalTree);
int sym_saveVar(TreeItem **sym_subtree,char* key);
bool isVarDeclared(SymStack* myStack, char* key);
void sym_inorder(TreeItem *tree);
int createSubTree(SymStack* myStack);
int symNewStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree);
SymTreeRoot* treeCreateRoot();
int symDisposeStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree);
int symtableInit(symtable* sym);

#endif