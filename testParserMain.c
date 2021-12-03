#include "Parser.h"
//#include "Scanner.h"
int main(){
    //printf("Meky Zbirka\n");
    TokenList *list=(TokenList*)malloc(sizeof(TokenList));
    listInit(list);
    ASTtree* abstractTree = ASTtreeCreate();
    int result=Parse(list, abstractTree);
    if(result==PARC_TRUE){
        printf("\nASTtree---------------------------------------------------\n\n");
        
        ASTprintStatement(abstractTree->tree);
        interpret(abstractTree->tree->TStatement.root);
        printf("Meky Zbirka jubilejny koncert\n");
    }
    else if (result==PARC_FALSE){
        
        printf("%d Jozko Vajda",result);
    }
    else if (result==LEXICAL_ERROR)
    {
        printf("%d Marika Gombitova",result);
    }
    
    else if(result==10){
        printf("my global treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
        //sym_inorder(mySymtable->sym_globalTree);
        printf("\nkoniec suboru");
    }

    return 0;
}