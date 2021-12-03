//#include "stack.h"
#include "Parser.h"
//#include "Scanner.h"

int expressionSemanticCheck(Tree *exprTree);

int isExpresionright(Tree *exprTree){
    int isOK = expressionSemanticCheck(exprTree);
    if (isOK == SEMANTICAL_COMPABILITY_ERROR){
        return isOK;
    }
    else if (isOK == DIVISION_ZERO_ERROR){
        return DIVISION_ZERO_ERROR;
    }
    else if (isOK == NIL_ERROR){
        return isOK;
    }
    return PROGRAM_OK;
}


int expressionSemanticCheck(Tree *exprTree){
    int left, right, unary;

    if (exprTree->Data->type == Plus || exprTree->Data->type == Minus || \
        exprTree->Data->type == Concatenation || exprTree->Data->type == Multiplication || \
        exprTree->Data->type == Less ){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);
        if (left == right){
            return right;
        }
        else if ((left == 0 && right == Integer) || (left == Integer && right == 0)){
            return Integer;
        }
        else if((left == Number && right == Integer)|| (right == Number && left == Integer) || \
                 (left == Number && right == 0) || (left == 0 && right == Number)){
            return Number;
        }
        
        else if (left == DIVISION_ZERO_ERROR || right == DIVISION_ZERO_ERROR){
            return DIVISION_ZERO_ERROR;
        }
        else if ((right == 5 || left == 5) || (left == NIL_ERROR || right == NIL_ERROR)){
            return NIL_ERROR;
        }
        else if (left != right){
            return SEMANTICAL_COMPABILITY_ERROR;
        }
    }

    else if (exprTree->Data->type == Sizeof){
        unary = expressionSemanticCheck(exprTree->attr.unary.child);
        if (unary == 0){
            return 0;
        }
        else if (unary == String){
            return Integer;
        }   
    }

    else if (exprTree->Data->type == Division || exprTree->Data->type == Division_integer ){
        right = expressionSemanticCheck(exprTree->attr.binary.right);
        left = expressionSemanticCheck(exprTree->attr.binary.left);

        if (right == 0){
            return DIVISION_ZERO_ERROR;
        }
        else if ((right == 5 || left == 5) || (left == NIL_ERROR || right == NIL_ERROR)){
            return NIL_ERROR;
        }
        else if (right == left){
            return PROGRAM_OK;
        }
    }

    else if (exprTree->Data->type == Not_equal || exprTree->Data->type == Is_equal){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);
        if (left == right){
            return left;
        }
        else if (left == 5 || right == 5){
            return 5;
        }
        else if (left != right){
            return SEMANTICAL_COMPABILITY_ERROR;
        }
    }

    else if (exprTree->Data->type == Integer){
        if (exprTree->Data->data.integer == 0){
            return 0;
        }
        return Integer;
    }

    else if (exprTree->Data->type == String){
        if (strlen(exprTree->Data->data.string) == 0){
            return 0;
        }
        return String;
    }

    else if (exprTree->Data->type == Number){
        return Number;
    }

    else if (strcmp("nil", exprTree->Data->data.string) == 0){
        return 5;
    }
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
        status = isExpresionright(exprTree);
        if (status == 0){
            printTree(exprTree);
            printf("OK\n");
        }
        else if(status == SEMANTICAL_COMPABILITY_ERROR){
            printf("semantic mistake\n");
        }
        else if (status == DIVISION_ZERO_ERROR){
            printf("DIVISION ZERO ERROR\n");
        }
        else if (status == NIL_ERROR){
            printf("NIL ERROR\n");
        }
        return status;
    }
    else{
        puts("CHYBA");
        printf("%i", status);
        return status;
    }
}