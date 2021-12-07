
#include "symtable.h"
#include "Parser.h"
#include "stdbool.h"
//#include "Scanner.h"
int main(){
    
    
    TokenList list;
    listInit(&list);
    int end=0;
    TreeItem *sym_globalTree=NULL;
    SymTreeRoot *sym_subTree=(SymTreeRoot *)malloc(sizeof(SymTreeRoot));
    sym_subTree->tree==NULL;
    SymStack *sym_stack=(SymStack*)malloc(sizeof(SymStack));
    TreeItem* symCurrentVar;
    symStackInit(sym_stack);
    int nb=0;
    while(nb<4){
        Token* mytoken = tokenCreate();
        if(mytoken == NULL){
            return 10;
        }
        end=tokenScan(stdin, &list, mytoken);
        if (end == 0){
                sym_saveFun(&sym_globalTree,&sym_subTree, sym_stack,mytoken->data.string);              
                if (strcmp(mytoken->data.string,"global")==0){
                    sym_saveVar((&sym_subTree->tree),"x",&symCurrentVar);
                    sym_saveVarType(symCurrentVar,"nil");
                    printf("haloo2\n");
                    //sym_inorder(sym_subTree->tree);
        
                    symNewStackBlock(sym_stack,&sym_subTree);           //cyklus||podmienka||whatever
                    
                    sym_saveVar((&sym_subTree->tree),"e",&symCurrentVar);
                    sym_saveVarType(symCurrentVar,"nil");
                    sym_saveVar((&sym_subTree->tree),"f",&symCurrentVar);
                    sym_saveVarType(symCurrentVar,"integer");
            
                    symNewStackBlock(sym_stack,&sym_subTree);           //cyklus||podmienka||whatever
                    
                    sym_saveVar((&sym_subTree->tree),"n",&symCurrentVar);
                    sym_saveVar((&sym_subTree->tree),"p",&symCurrentVar);

                    if (sym_varType(sym_stack, "x")!=-1){
                        printf("\nhiiiiiiiiiiiiiiiii %d\n",sym_varType(sym_stack, "x"));
                    }
                    else{
                        printf("\nfalse\n");
                    }

                    
                    symDisposeStackBlock(sym_stack, &sym_subTree);

                    
                    //printf("haloo2\n");
                    //sym_inorder(sym_globalTree);
                    //sym_inorder(sym_subTree->tree);

                }
                //printStack(sym_stack);
                
                symDisposeStackBlock(sym_stack, &sym_subTree);
        }
        nb++;
    }
    //symDisposeStackBlock(sym_stack, &sym_subTree);
    //printf("no co %s\n", sym_subTree->tree->key);
    sym_inorderGlobal(sym_globalTree);
    printf("heloooooooooo %d",sym_globalTree->subtree->tree->type);
    

    //symDisposeStackBlock(sym_stack);
    //sym_inorder(sym_globalTree);
    //printf("\nsubtre:\n");
    

    
    //printf("subtree: %s\n",sym_globalTree->rptr->subtree->tree->lptr->key);
    
    
    
    return 0;
}