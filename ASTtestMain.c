#include "AST.h"
int main(){
    printf("MEKY ZBIRKA\n");
    ASTstack *myStack=(ASTstack*)malloc(sizeof(ASTstack));
    ASTstackInit(myStack);
    Tstate* tree= ASTcreateLeaf(ASTglobal);
    ASTStackPush(myStack, tree);
    
    ASTaddFCToTree(myStack);
    //ASTendStatement(myStack);
    ASTaddFCToTree(myStack);
    
    //ASTaddFCToTree(myStack);
    //ASTendStatement(myStack);



    printf("mytree:\n\n");
    //printf("%d",tree->TStatement.root->statements[0]->type);
    ASTprintStatement(tree);
    //ASTprintStack(myStack);
    return 0;//*tree->TStatement.root->nbStatements;
    
}