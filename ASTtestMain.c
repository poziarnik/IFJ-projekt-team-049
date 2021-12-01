#include "AST.h"
int main(){
    printf("MEKY ZBIRKA\n");
    /*ASTstack *myStack=(ASTstack*)malloc(sizeof(ASTstack));
    ASTstackInit(myStack);
    Tstate* tree= ASTcreateLeaf(ASTglobal);
    ASTStackPush(myStack, tree);*/
    ASTtree* abstractTree = ASTtreeCreate();
    
    ASTaddFCToTree(abstractTree->ASTStack);

    //ASTendStatement(myStack);
    for (int i = 0; i < 200; i++)
    {
        ASTaddCycleToTree(abstractTree->ASTStack);
        ASTendStatement(abstractTree->ASTStack);
        ASTaddAssigmentToTree(abstractTree->ASTStack);
        ASTendStatement(abstractTree->ASTStack);
    }
    //ASTendStatement(abstractTree->ASTStack);
    ASTaddFCToTree(abstractTree->ASTStack);
    ASTendStatement(abstractTree->ASTStack);
    //ASTaddFCToTree(myStack);



    printf("mytree:\n\n");
    //printf("%d",tree->TStatement.root->statements[0]->type);
    ASTprintStatement(abstractTree->tree);
    //ASTprintStack(myStack);
    return 0;//*tree->TStatement.root->nbStatements;
    
}