//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"

int expressionSemanticCheck(Tree *exprTree){
    int left, right, unary;

    if (exprTree->Data->type == Plus){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);
        if (left == right){
            return PROGRAM_OK;
        } 
    }
    
    else if (exprTree->Data->type == Integer){
        return Integer;

    }


    return -1;
    
}




int main(){

    TokenList list;
    listInit(&list);
    Token* MyToken = tokenCreate();
    tokenScan(stdin,&list,MyToken);
    int status;
    Tree *exprTree;
    status = expressionCheck(MyToken,&list, exprTree);
    if (status == 0){
        printTree(exprTree);
        return status;
    }
    else{
        puts("CHYBA");
        printf("%i", status);
        return status;
    }
    

    
    
}