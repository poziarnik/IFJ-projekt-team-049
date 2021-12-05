
#include "symtable.h"
#include "Parser.h"
#include "stdbool.h"
//#include "Scanner.h"
int main(){
    
    
    TokenList list;
    listInit(&list);
    int end=0;
    TreeItem *sym_globalTree=NULL;
    SymTreeRoot *sym_subTree;
    sym_subTree->tree==NULL;
    SymStack *sym_stack=(SymStack*)malloc(sizeof(SymStack));
    symStackInit(sym_stack);
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
                
                sym_saveFun(&sym_globalTree,&sym_subTree, sym_stack,mytoken->data.string);              
                
                sym_saveVar((&sym_subTree->tree),"c");
                sym_saveVar((&sym_subTree->tree),"b");
                sym_saveVar((&sym_subTree->tree),"a");
                sym_saveVar((&sym_subTree->tree),"d");
                printf("atribut: %s\ntyp: %i\n",mytoken->data.string, mytoken->type);
            }

        }
    }
    symNewStackBlock(sym_stack, &sym_subTree);
    sym_saveVar((&sym_subTree->tree),"e");
    sym_saveVar((&sym_subTree->tree),"f");
    //symDisposeStackBlock(sym_stack);
    sym_inorder(sym_globalTree);
    printf("\nsubtre:\n");
    sym_inorder(sym_subTree->tree);
    //printf("subtree: %s\n",sym_globalTree->rptr->subtree->tree->lptr->key);
    if (isVarDeclared(sym_stack, "c")){
        printf("\ntrue\n");
    }
    else
    {
        printf("\nfalse\n");
    }
    
    return 0;
}