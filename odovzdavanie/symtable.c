/**
 *
 * @file symtable.c
 * @author Juraj Hatala
 * @brief 
 * @date 
 *
 */

#include "symtable.h"
#include <stdio.h>
#include <stdbool.h>
/**
 * @brief vlozi item do zadaneho binarneho stromu podla kluca
 * 
 * @param tree 
 * @param key 
 * @param new 
 */
void bst_insert(TreeItem **tree, char* key, TreeItem *new){ 
  if ((*tree) == NULL){
    new->key = key;
    (*tree) = new;
  }
  else{
    if (strcmp(key, (*tree)->key)<0){
      bst_insert(&((*tree)->lptr), key, new);
    }
    else{
      if (strcmp(key, (*tree)->key)>0){
        bst_insert(&((*tree)->rptr), key, new);
      }
      /*else{
        (*tree)->data = data;
      }  */
    }  
  }
}
/**
 * @brief inicializuje ukazatele v treeitem na NULL
 * 
 * @param treeitem 
 */
void TreeItemInit(TreeItem *treeitem){
  treeitem->lptr = NULL;
  treeitem->rptr = NULL;
  treeitem->data = NULL;
  treeitem->subtree=NULL;
}
/**
 * @brief zisti ci sa v strome nachadza prvok so zadanym klucom
 * 
 * @param tree 
 * @param key 
 * @return true 
 * @return false 
 */
bool sym_search(TreeItem *tree, char* key) {
  if (tree == NULL){
    return false;
  }
  else{
    if (strcmp(key, tree->key)==0){
      //printf("*%s\n",tree->key);
      return true;
    }
    else{
      if (strcmp(key, tree->key)<0){
        sym_search(tree->lptr, key);
      }
      else{
        sym_search(tree->rptr, key);
      }
    }
  }
  return false;
}
/**
 * @brief zahodi vrch zasobnika
 * 
 * @param myStack 
 */
void symStackPop(SymStack *myStack){
    SymStackElement* tmp;
    if (myStack->head!=NULL){
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
}
/**
 * @brief vytvori novy element stacku a vlozi do neho zadany strom
 * 
 * @param myStack 
 * @param tree 
 * @return int
 *  
 */
int symStackPush(SymStack* myStack, SymTreeRoot* tree){
    SymStackElement* newSymbol=(SymStackElement*)malloc(sizeof(SymStackElement));
    if (newSymbol==NULL) return INTERNAL_ERROR;
    
    newSymbol->root=tree;
    newSymbol->next=NULL;
    if (myStack->head!=NULL){
        newSymbol->next=myStack->head;
        myStack->head=newSymbol;
    }
    else{
        myStack->head=newSymbol;
    }
    return 0;
}
/**
 * @brief do zadaneho stromu vlozi vrch stacku
 * 
 * @param myStack 
 * @param tree 
 */
void symStackTop(SymStack* myStack, SymTreeRoot* tree){
    if (myStack->head!=NULL){
        tree=myStack->head->root;
    }
}
/**
 * @brief inicializue head stacku na NULL
 * 
 * @param myStack 
 */
void symStackInit(SymStack* myStack){
  myStack->head=NULL;
}
/**
 * @brief allokuje pamet pre treeItem, treba kontrolovat chybu pri malloc 
 * 
 * @return TreeItem* 
 */
TreeItem* treeCreate(){
    TreeItem* newTree=(TreeItem*)malloc(sizeof(TreeItem));
    if(newTree==NULL){
        return NULL;
    }
    sym_treeInit(newTree);
    return newTree;
}
/**
 * @brief allokuje pamat pre treeRoot, treba kontrolovat chybu pri malloc
 * 
 * @return SymTreeRoot* 
 */
SymTreeRoot* treeCreateRoot(){
    SymTreeRoot* newRoot=(SymTreeRoot*)malloc(sizeof(SymTreeRoot));
    if(newRoot==NULL){
        return NULL;
    }
    newRoot->tree=NULL;
    return newRoot;
}
/**
 * @brief ??!!
 * 
 * @param newTree 
 */
void sym_treeInit(TreeItem *newTree){
    newTree=NULL;
}
/**
 * @brief Vytvori novy item v global tree s kluco key a v novom iteme vytvori novy subtree a pushne ho na stack. Vonkajsi hlavny ukazatel subtree nastavi na novy subtree
 * 
 * @param sym_globalTree 
 * @param sym_subTree 
 * @param myStack 
 * @param key 
 * @return int 
 */
int sym_saveFun(TreeItem **sym_globalTree, SymTreeRoot **sym_subTree, SymStack* myStack, char* key){
  tData* data=(tData*)malloc(sizeof(tData));                    //vytvor data
  data->varType=0;

  TreeItem *newItem = (TreeItem*)malloc(sizeof(TreeItem));          //vytvor novy item
  if(newItem==NULL) return INTERNAL_ERROR;
  TreeItemInit(newItem);
  
  newItem->subtree=treeCreateRoot();                                //vytvor na newitem vetvu pre subtree
  if (newItem->subtree==NULL) return INTERNAL_ERROR;
  //newItem->subtree->tree==NULL;                                     //koren musi ukazovat na null

  *sym_subTree=newItem->subtree;                                    //vonkajsi ukazatel ukazuje na posledno vytvoreny subtree 
  symStackPush(myStack, newItem->subtree);                          //pushni na symstack

  newItem->data=data;
  bst_insert(sym_globalTree, key, newItem);                       //vloz item do global tree
  return 0;
}
/**
 * @brief Vytvori novy item s klucom key a vlozi ho do current subtree
 * 
 * @param sym_subtree 
 * @param key 
 * @return int 
 */
int sym_saveVar(TreeItem **sym_subtree,char* key){
  tData* data=(tData*)malloc(sizeof(tData));                    //vytvor data
  data->varType=1;
  
  TreeItem *newItem = (TreeItem*)malloc(sizeof(TreeItem));          //vytvor novy item
  if(newItem==NULL) return INTERNAL_ERROR;
  TreeItemInit(newItem);
  newItem->data=data;
  
  bst_insert(sym_subtree, key, newItem);                   //vloz do current subtree
  return 0;
}
/**
 * @brief Vypise zadany strom inorder na stdout
 * 
 * @param tree 
 */
void sym_inorder(TreeItem *tree) {
  if (tree != NULL){
    sym_inorder(tree->lptr);
    printf("%s\n", tree->key);
    sym_inorder(tree->rptr);
  }
}
/**
 * @brief Zisti ci sa v globalTree nachadza item s klucom key 
 * 
 * @param key 
 * @param globalTree 
 * @return true 
 * @return false 
 */
bool isFunDeclared(char* key, TreeItem* globalTree){
  if(sym_search(globalTree, key) || isInbuildFun(key)){
    return true;
  }
  return false;
}
/**
 * @brief zisti ci sa na stacku nachadza item s klucom key
 * 
 * @param myStack 
 * @param key 
 * @return true 
 * @return false 
 */
bool isVarDeclared(SymStack* myStack, char* key){
  SymStackElement* tmp=myStack->head;
  while(tmp!=NULL){
    if(sym_search(tmp->root->tree, key)) return true;
    tmp=tmp->next;
  }
  return false;
}
/**
 * @brief Vytvora novy block na stacku. Pri volani cyklov condition...
 * 
 * @param myStack 
 * @param sym_subTree 
 * @return int 
 */
int symNewStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree){
  SymTreeRoot* newRoot = treeCreateRoot();
  if(newRoot==NULL) return INTERNAL_ERROR;
  symStackPush(myStack, newRoot);
  *sym_subTree= newRoot;
  return 0;
}
/**
 * @brief ??!!!
 * 
 * @param myStack 
 * @param sym_subTree 
 * @return int 
 */
int symDisposeStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree){ //odstran vrch stacku a zmen ukazatel na subtree
  if (myStack->head!=NULL){
    SymStackElement* tmp=myStack->head;
    myStack->head=myStack->head->next;
    *sym_subTree=tmp->root;//myStack->head->root;
  }
  return 0;  
} 
/**
 * @brief Inicializuje symtable vytvori v nej stack, zvysne ukazatele nastavi na NULL 
 * 
 * @param sym 
 * @return int 
 */
int symtableInit(symtable* sym){
  SymStack *symstack=(SymStack*)malloc(sizeof(SymStack));
  if(symstack==NULL) return INTERNAL_ERROR;
  symStackInit(symstack);
  sym->sym_stack=symstack;
  sym->sym_globalTree=NULL;
  return 0;
}
/**
 * @brief Zistuje ci je str jedna z inbuild funkcii
 * 
 * @param str 
 * @return true 
 * @return false 
 */
bool isInbuildFun(char* str){
  if(strcmp(str,"write")==0 || strcmp(str,"read")==0 || strcmp(str,"readi")==0 \
  || strcmp(str,"reads")==0 || strcmp(str,"readn")==0 || strcmp(str,"tointeger")==0 \
  || strcmp(str,"substr")==0 || strcmp(str,"ord")==0 || strcmp(str,"chr")==0) return true;
  else return false;
}