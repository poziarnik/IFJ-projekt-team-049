#include "symtable.h"
#include "Parser.h"
#include "stdbool.h"
//#include "Scanner.h"
int main(){

    TokenList list;
    listInit(&list);
    int end=0;

    /*TreeItem *sym_globalTree=NULL;
    SymTreeRoot *sym_subTree;
    SymStack *sym_stack=(SymStack*)malloc(sizeof(SymStack));
    symStackInit(sym_stack);*/

    symtable* sym=(symtable*)malloc(sizeof(symtable));
    symtableInit(sym);

    while(end!=10){
        Token* mytoken = tokenCreate();
        if(mytoken == NULL){
            return 10;
        }
        end=tokenScan(stdin, &list, mytoken);
        if (end == 0){
            printf("----------------------------------------------------------\n");
            if ((mytoken->type == Integer) || (mytoken->type == Number)){
                printf("atribut: %f\ntyp: %i\n",mytoken->data.number, mytoken->type);
            }
            else{
                sym_saveFun(&sym->sym_globalTree,&sym->sym_subTree, sym->sym_stack,mytoken->data.string);              
                
                sym_saveVar((&sym->sym_subTree->tree),"c");
                sym_saveVar((&sym->sym_subTree->tree),"b");
                sym_saveVar((&sym->sym_subTree->tree),"a");
                sym_saveVar((&sym->sym_subTree->tree),"d");
                printf("atribut: %s\ntyp: %i\n",mytoken->data.string, mytoken->type);
            }

        }
    }
    symNewStackBlock(sym->sym_stack, &sym->sym_subTree);
    sym_saveVar((&sym->sym_subTree->tree),"e");
    sym_saveVar((&sym->sym_subTree->tree),"f");
    
    printf("stack %s\n",sym->sym_stack->head->root->tree->key);
    symDisposeStackBlock(sym->sym_stack, &sym->sym_subTree);
    printf("stack %s\n",sym->sym_stack->head->root->tree->key);
    

    sym_inorder(sym->sym_globalTree);
    printf("\nsubtre:\n");
    sym_inorder(sym->sym_subTree->tree);
    //printf("subtree: %s\n",sym_globalTree->rptr->subtree->tree->lptr->key);
    if (isVarDeclared(sym->sym_stack, "e")){
        printf("\ntrue\n");
    }
    else
    {
        printf("\nfalse\n");
    }
    
    return 0;
}