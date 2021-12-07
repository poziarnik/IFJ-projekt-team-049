#include "Parser.h"
//#include "Scanner.h"
int main(){
    //printf("Meky Zbirka\n");
    
    ASTtree* abstractTree = ASTtreeCreate();

    symtable* mySymtable=(symtable*)malloc(sizeof(symtable));
    if (mySymtable == NULL) return INTERNAL_ERROR;
    symtableInit(mySymtable); 

    int result=Parse(abstractTree, mySymtable);
    if(result==PARC_TRUE){
        printf("\nASTtree---------------------------------------------------\n\n");
        
        ASTprintStatement(abstractTree->tree);

        printf("\nSymTable---------------------------------------------------\n\n");

        sym_inorderGlobal(mySymtable->sym_globalTree);
        //interpret(abstractTree->tree->TStatement.root);
        printf("\nMeky Zbirka jubilejny koncert\n");
    }
    else if (result==PARC_FALSE){
        
        printf("%d Jozko Vajda",result);
    }
    else if (result==LEXICAL_ERROR)
    {
        printf("%d Marika Gombitova",result);
    }
    else if (result==SEMANTICAL_NODEFINITION_REDEFINITION_ERROR){
        printf("%d nesmrtelny Kaja",result);
    }
    
    else if(result==10){
        printf("my global treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
        //sym_inorder(mySymtable->sym_globalTree);
        printf("\nkoniec suboru");
    }
    else {
        printf("%i", result);
    }

    return result;
}