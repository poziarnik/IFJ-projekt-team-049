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

void bst_insert(TreeItem **tree, char* key, tData* data) {
  
  if ((*tree) == NULL){
    TreeItem *new = (TreeItem*)malloc(sizeof(TreeItem));
    new->key = key;
    new->data = data;
    new->lptr = NULL;
    new->rptr = NULL;
    (*tree) = new;
  }
  else{
    if (strcmp(key, (*tree)->key)<0){
      bst_insert(&((*tree)->lptr), key, data);
    }
    else{
      if (strcmp(key, (*tree)->key)>0){
        bst_insert(&((*tree)->rptr), key, data);
      }
      else{
        (*tree)->data = data;
      }  
    }  
  }
}

bool bst_search(TreeItem *tree, char* key) {
  if (tree == NULL){
    return false;
  }
  else{
    if (strcmp(key, tree->key)==0){
      return true;
    }
    else{
      if (strcmp(key, tree->key)<0){
        bst_search(tree->lptr, key);
      }
      else{
        bst_search(tree->rptr, key);
      }
    }
  }
  return false;
}

void stackPop(sym_stack *myStack){
    sym_element* tmp;
    if (myStack->head!=NULL){
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
}
 
int stackPush(sym_stack* myStack, TreeItem* tree){
    sym_element* newSymbol=(sym_element*)malloc(sizeof(sym_element));
    if (newSymbol==NULL){
        return 1;
    }
    newSymbol->tree=tree;
    if (myStack->head!=NULL){
        newSymbol->next=myStack->head;
        myStack->head=newSymbol;
    }
    else{
        myStack->head=newSymbol;
    }
    return 0;
}
void stackTop(sym_stack* myStack, TreeItem* tree){
    if (myStack->head!=NULL){
        tree=myStack->head->tree;
    }
}

int treeCreate(TreeItem *newTree){
    newTree=(TreeItem*)malloc(sizeof(TreeItem));
    if(newTree==NULL){
        return 3;
    }
    treeInit(newTree);
    return 0;
}
void treeInit(TreeItem *newTree){
    newTree=NULL;
}
int createSubTree(sym_stack* myStack){                        //pri volani funkcie cyklu atd...
    TreeItem* newtree;
    treeCreate(newtree);
    stackPush(myStack, newtree);
}
//funkcia na vyhladavanie identifikatora
//funkcia na ulozenie identifikatora<funkcia na vyhladavanie identifikatora
int saveIdentifier()
