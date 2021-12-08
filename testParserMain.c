#include "Parser.h"
//#include "Scanner.h"
int main(){
    //printf("Meky Zbirka\n");
    
    ASTtree* abstractTree = ASTtreeCreate();

    symtable* mySymtable=(symtable*)malloc(sizeof(symtable));
    if (mySymtable == NULL) return INTERNAL_ERROR;
    symtableInit(mySymtable); 

    int result=Parse(abstractTree, mySymtable);
    // if(result == PROGRAM_OK) interpret(abstractTree->tree->TStatement.root);
    fprintf(stderr, "%i\n", result);

    return result;
}