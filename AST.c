
#include "AST.h"

/*podla typu prejde cestu od stack head po statements blok*/

ASTtree* ASTtreeCreate(){
    ASTtree* newTree = (ASTtree*)malloc(sizeof(ASTtree)); 
    if (newTree==NULL){
        return NULL;
    }
    
    newTree->ASTStack=(ASTstack*)malloc(sizeof(ASTstack));
    if (newTree->ASTStack==NULL){
        return NULL;
    }
    ASTstackInit(newTree->ASTStack);

    newTree->tree = ASTcreateLeaf(ASTglobal);
    ASTStackPush(newTree->ASTStack, newTree->tree);
    return newTree;
}
Tstate*** ASTreturnFastST(ASTstack* myStack){
    statementType Type=myStack->head->statement->type;
    if (Type==ASTfunction){
        return &(myStack->head->statement->TStatement.function->statements);
    }
    else if(Type==ASTglobal){
        return &(myStack->head->statement->TStatement.root->statements);
    }
    else if (Type==ASTcycle){
        return &(myStack->head->statement->TStatement.while_loop->do_statement);
    }
    else return NULL;   
}

/*podla typu prejde cestu od stack head po statementNb*/
int* ASTreturnFastNB(ASTstack* myStack){
    statementType Type=myStack->head->statement->type;
    if (Type==ASTfunction){
        return myStack->head->statement->TStatement.function->nbStatements;
    }
    else if( Type==ASTglobal){
        return myStack->head->statement->TStatement.root->nbStatements;
    }
    else if (Type==ASTcycle){
        return myStack->head->statement->TStatement.while_loop->nbStatements;
    }
    else return 0;
}
int ASTStackPush(ASTstack* myStack, Tstate* newStatement){
    ASTstackElement* newElement=(ASTstackElement*)malloc(sizeof(ASTstackElement));
    if (newElement==NULL) return INTERNAL_ERROR;
    newElement->statement=newStatement;
    newElement->next=NULL;

    if (myStack->head!=NULL){
        newElement->next=myStack->head;
        myStack->head=newElement;
    }
    else{
        myStack->head=newElement;
    }
    return 0;
}
int ASTaddFCToTree(ASTstack* myStack){
    Tstate* newStatement=ASTcreateLeaf(ASTfunction);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);

    return 0;
}
int ASTaddCycleToTree(ASTstack* myStack){
    Tstate* newStatement=ASTcreateLeaf(ASTcycle);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);
    
    return 0;
}
int ASTaddDefineToTree(ASTstack* myStack){
    Tstate* newStatement=ASTcreateLeaf(ASTdefine);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);

    return 0;
}
int ASTaddAssigmentToTree(ASTstack* myStack){
    Tstate* newStatement=ASTcreateLeaf(ASTassigne);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);

    return 0;
}
int ASTaddFCcallToTree(ASTstack* myStack){
    Tstate* newStatement=ASTcreateLeaf(ASTfunctionCall);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);

    return 0;
}
Tstate** ASTcreateStatements(int* nbStatements){
    //printf("imhere");
    Tstate** statements=(Tstate**)malloc(50*sizeof(Tstate*));
    for (int i = 0; i < 49; i++){
        statements[i]=NULL;
    }
    *nbStatements=0;

    return statements;
}
int ASTaddToStatements(Tstate*** statements, int* nbStatements, Tstate* newStatement){
    int sizeOfArray=0;                    //odvozdujem velkost pola
    if (*nbStatements<50){
        sizeOfArray=50;
    }
    else{
        sizeOfArray=50*((*nbStatements / 50) + 1);
    }

    if(*nbStatements == (sizeOfArray)-1){           //-2 aby bol posledny znak vzdy null
        *statements = (Tstate**)realloc(*statements, sizeof(Tstate*)*(sizeOfArray+50));
        printf("imhere %d",sizeOfArray);
        if (*statements == NULL){
            return INTERNAL_ERROR;
        }
    }
    
    (*statements)[*nbStatements]=newStatement;
    *nbStatements = *nbStatements +1;               //pridam newstatement na nove miesto v poli
    return 0;
}
Tree** ASTcreateExpressions(int* nbExpressions){
    printf("imhere");
    Tree** espressions=(Tree**)malloc(50*sizeof(Tree*));
    for (int i = 0; i < 49; i++){
        espressions[i]=NULL;
    }
    *nbExpressions=0;

    return espressions;
}
int ASTaddToExpressions(Tree*** espressions, int* nbExpressions, Tree* newExpression){
    int sizeOfArray=0;                    //odvozdujem velkost pola
    if (*nbExpressions<50){
        sizeOfArray=50;
    }
    else{
        sizeOfArray=50*((*nbExpressions / 50) + 1);
    }

    if(*nbExpressions == (sizeOfArray)-1){           //-2 aby bol posledny znak vzdy null
        *espressions = (Tree**)realloc(*espressions, sizeof(Tree*)*(sizeOfArray+50));
        printf("imhere %d",sizeOfArray);
        if (*espressions == NULL){
            return INTERNAL_ERROR;
        }
    }
    
    (*espressions)[*nbExpressions]=newExpression;
    *nbExpressions = *nbExpressions +1;               //pridam newstatement na nove miesto v poli
    return 0;
}
Token** ASTcreateTokenArray(int* nbTokens){
    //printf("imhere");
    Token** array=(Token**)malloc(50*sizeof(Token*));
    for (int i = 0; i < 49; i++){
        array[i]=NULL;
    }
    *nbTokens=0;

    return array;
}
int ASTaddToTokenArray(Token*** array, int* nbTokens, Token* newToken){
    int sizeOfArray=0;                    //odvozdujem velkost pola
    if (*nbTokens<50){
        sizeOfArray=50;
    }
    else{
        sizeOfArray=50*((*nbTokens / 50) + 1);
    }

    if(*nbTokens == (sizeOfArray)-1){           
        *array = (Token**)realloc(*array, sizeof(Token*)*(sizeOfArray+50));
        printf("imhere %d",sizeOfArray);
        if (*array == NULL){
            return INTERNAL_ERROR;
        }
    }
    
    (*array)[*nbTokens]=newToken;
    *nbTokens = *nbTokens +1;               //pridam newstatement na nove miesto v poli
    return 0;
}
/*(stackpop) dorobit uvolnovanie veci ak bude cas*/
void ASTendStatement(ASTstack *myStack){
    ASTstackElement* tmp;
    if (myStack->head!=NULL){
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
}

Tstate* ASTcreateLeaf(statementType type){
    Tstate* newLeaf=(Tstate*)malloc(sizeof(Tstate));
    if(type==ASTglobal){
        //-alokovat strukturu
        newLeaf->type=ASTglobal;
        newLeaf->TStatement.root = (root*)malloc(sizeof(root));
        //---alokovat statementy
        newLeaf->TStatement.root->nbStatements = (int*)malloc(sizeof(int));
        (*newLeaf->TStatement.root->nbStatements)=0;
        newLeaf->TStatement.root->statements = ASTcreateStatements(newLeaf->TStatement.root->nbStatements);
    }
    else if (type==ASTfunction){
        //-alokovat strukturu
        newLeaf->type=ASTfunction;
        newLeaf->TStatement.function = (TFunction_tree*)malloc(sizeof(TFunction_tree)); 
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.function->id = (Token*)malloc(sizeof(Token));
        newLeaf->TStatement.function->nbParameters = (int*)malloc(sizeof(int));
        newLeaf->TStatement.function->nbReturntypes = (int*)malloc(sizeof(int));
        newLeaf->TStatement.function->parameters = ASTcreateTokenArray(newLeaf->TStatement.function->nbParameters);
        newLeaf->TStatement.function->returnTypes = ASTcreateTokenArray(newLeaf->TStatement.function->nbReturntypes); 
        //---alokovat statementy
        newLeaf->TStatement.function->nbStatements = (int*)malloc(sizeof(int));
        (*newLeaf->TStatement.function->nbStatements)=0;
        newLeaf->TStatement.function->statements = ASTcreateStatements(newLeaf->TStatement.function->nbStatements);
    }
    else if (type==ASTcycle){
        //-alokovat strukturu
        newLeaf->type=ASTcycle;
        newLeaf->TStatement.while_loop = (TWhile_tree*)malloc(sizeof(TWhile_tree));
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.while_loop->expression = (Tree*)malloc(sizeof(Tree));
        //---alokovat statementy
        newLeaf->TStatement.while_loop->nbStatements = (int*)malloc(sizeof(int));
        (*newLeaf->TStatement.while_loop->nbStatements)=0;
        newLeaf->TStatement.while_loop->do_statement = ASTcreateStatements(newLeaf->TStatement.while_loop->nbStatements);
    }
    else if (type==ASTdefine){
        //-alokovat strukturu
        newLeaf->type=ASTdefine;
        newLeaf->TStatement.definiton = (TDefinition_tree*)malloc(sizeof(TDefinition_tree));
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.definiton->id=(Token*)malloc(sizeof(Token));
        newLeaf->TStatement.definiton->data_type=(Token*)malloc(sizeof(Token));
        newLeaf->TStatement.definiton->expression=(Tree*)malloc(sizeof(Tree));
    }
    else if (type==ASTassigne){
        //-alokovat strukturu
        newLeaf->type=ASTassigne;
        newLeaf->TStatement.assignment = (TAssign_tree*)malloc(sizeof(TAssign_tree));
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.assignment->nbID = (int*)malloc(sizeof(int));
        newLeaf->TStatement.assignment->nbexpressions = (int*)malloc(sizeof(int));
        *(newLeaf->TStatement.assignment->nbID)=0;
        *(newLeaf->TStatement.assignment->nbexpressions)=0;
        newLeaf->TStatement.assignment->ID = ASTcreateTokenArray(newLeaf->TStatement.assignment->nbID);
        newLeaf->TStatement.assignment->expressions = ASTcreateExpressions(newLeaf->TStatement.assignment->nbexpressions);
    }
    else if (type==ASTfunctionCall){
        //-alokovat strukturu
        newLeaf->type=ASTfunctionCall;
        newLeaf->TStatement.functioncall = (TFunctioncall_tree*)malloc(sizeof(TFunctioncall_tree));
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.functioncall->functionName = (Token*)malloc(sizeof(Token));
        newLeaf->TStatement.functioncall->nbID = (int*)malloc(sizeof(int));
        newLeaf->TStatement.functioncall->nbParameters = (int*)malloc(sizeof(int));
        newLeaf->TStatement.functioncall->ID = ASTcreateTokenArray(newLeaf->TStatement.functioncall->nbID);
        newLeaf->TStatement.functioncall->parameters = ASTcreateTokenArray(newLeaf->TStatement.functioncall->nbParameters);


    }
    else if (type==ASTcondition){
    }
    
    
    return newLeaf;
    
}
void ASTprintStatement(Tstate* statement){
    if(statement->type==ASTglobal) printf("root\n");
    else if(statement->type==ASTfunction) printf("function\n");
    else if(statement->type==ASTcycle) printf("loop\n");
    else if(statement->type==ASTdefine) printf("define\n");
    else if(statement->type==ASTassigne) printf("assigment\n");
    else if(statement->type==ASTfunctionCall) printf("functionCall\n");
    int nb=0;
    Tstate* tmp;
    while(true){
        if (statement->type==ASTfunction){
            tmp=statement->TStatement.function->statements[nb];
        }
        else if (statement->type==ASTglobal){
            tmp=statement->TStatement.root->statements[nb];
        }
        else if (statement->type==ASTcycle){
            tmp=statement->TStatement.while_loop->do_statement[nb];
        }
        nb=nb+1;
        if (tmp==NULL) break;
        ASTprintStatement(tmp);
    }
    if(statement->type==ASTglobal) printf("root end\n");
    else if(statement->type==ASTfunction) printf("function end\n");
    else if(statement->type==ASTcycle) printf("loop end\n");
    else if(statement->type==ASTdefine) printf("define end\n");
    else if(statement->type==ASTassigne) printf("assigment end\n");
    else if(statement->type==ASTfunctionCall) printf("functionCall end\n");
}
void ASTprintStack(ASTstack* myStack){
    ASTstackElement* tmp=myStack->head;
    while (tmp!=NULL){
        printf("%d ",tmp->statement->type);
        tmp=tmp->next;
    }
}
//void ASTnewStatementInit(Tstate* newStatement)
void ASTstackInit(ASTstack* myStack){
    myStack->head=NULL;
}
