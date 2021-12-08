
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
    ASTinBuildArrayInit(newTree->tree->TStatement.root->UsedInBuild);
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
    else if (Type==ASTcondition)
    {
        if(*(myStack->head->statement->TStatement.if_loop->hasElse)==false){//ak som pod ifom, tak pridavam do ifstatements
            
            return &(myStack->head->statement->TStatement.if_loop->if_statements);
        }
        else{//ak som pod elsom, pridavam do else statements
            return &(myStack->head->statement->TStatement.if_loop->else_statements);
        }
    }
    
    else return NULL;   
}

/*podla typu prejde cestu od stack head po statementNb*/
int* ASTreturnFastNB(ASTstack* myStack){
    
    statementType Type=myStack->head->statement->type;
    //printf(x ? "true" : "false" );
    if (Type==ASTfunction){
        return myStack->head->statement->TStatement.function->nbStatements;
    }
    else if( Type==ASTglobal){
        return myStack->head->statement->TStatement.root->nbStatements;
    }
    else if (Type==ASTcycle){
        return myStack->head->statement->TStatement.while_loop->nbStatements;
    }
    else if (Type==ASTcondition)
    {
        if(*(myStack->head->statement->TStatement.if_loop->hasElse)==false){
            return myStack->head->statement->TStatement.if_loop->nbIfStatements;
        }
        else{
            return myStack->head->statement->TStatement.if_loop->nbElseStatements;
        }
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

    if (myStack->head->statement->type==ASTdefine)
    {
        myStack->head->statement->TStatement.definiton->ExFc.FCcall=(Tstate*)malloc(sizeof(Tstate));
        if(myStack->head->statement->TStatement.definiton->ExFc.FCcall==NULL) return INTERNAL_ERROR;
        *myStack->head->statement->TStatement.definiton->state=FCcall;//uloz info o tom ze v definition zapisany fcCall
        *myStack->head->statement->TStatement.definiton->ExFc.FCcall = *newStatement;//uloz new statement do define na vrchu stromu
    }
    else ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    
    //pridaj do stromu na statements na vrchu stacku
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);

    return 0;
}
int ASTaddConditionToTree(ASTstack* myStack){
    
    Tstate* newStatement=ASTcreateLeaf(ASTcondition);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);
}
int ASTaddElseToCondition(ASTstack* myStack){
    if(myStack->head->statement->type==ASTcondition){
        *(myStack->head->statement->TStatement.if_loop->hasElse) = true;
        ASTallocateSpaceForElse(myStack);
    }
}
int ASTaddReturnToTree(ASTstack* myStack){
    Tstate* newStatement=ASTcreateLeaf(ASTreturn);
    if (newStatement==NULL){
        return INTERNAL_ERROR;
    }
    //pridaj do stromu na statements na vrchu stacku
    ASTaddToStatements(ASTreturnFastST(myStack), ASTreturnFastNB(myStack), newStatement);
    //pridaj na vrch stacku
    ASTStackPush(myStack, newStatement);
    
    return 0;
}
int ASTallocateSpaceForElse(ASTstack* myStack){
    //allokuj nbStatements
    myStack->head->statement->TStatement.if_loop->nbElseStatements = (int*)malloc(sizeof(int));
    if(myStack->head->statement->TStatement.if_loop->nbElseStatements==NULL) return INTERNAL_ERROR;
    *(myStack->head->statement->TStatement.if_loop->nbElseStatements)=0;
    //alokuj priestor pre dalsie statements
    myStack->head->statement->TStatement.if_loop->else_statements = ASTcreateStatements(myStack->head->statement->TStatement.if_loop->nbElseStatements); 
    if(myStack->head->statement->TStatement.if_loop->else_statements==NULL) return INTERNAL_ERROR;
    
    return 0;
}
int ASTswitchAssigneFCcall(ASTstack* myStack){
    if (myStack->head->statement->type==ASTassigne){
        Token** tmp=myStack->head->statement->TStatement.assignment->IDs;
        int nbIDs=*myStack->head->statement->TStatement.assignment->nbID;
        ASTendStatement(myStack);
        ASTaddFCcallToTree(myStack);
        for (int i = 0; i < nbIDs; i++){//prehodim vsetky id z assigneLeaf do noveho FCcall leaf
            ASTaddToTokenArray(&(myStack->head->statement->TStatement.functioncall->IDs),\
            myStack->head->statement->TStatement.functioncall->nbID,tmp[i]);
        }
        
    }
    else INTERNAL_ERROR;

    return 0;
}
Tstate** ASTcreateStatements(int* nbStatements){
    Tstate** statements=(Tstate**)malloc(50*sizeof(Tstate*));
    for (int i = 0; i < 49; i++){
        statements[i]=(Tstate*)malloc(sizeof(Tstate));
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
        if (*statements == NULL){
            return INTERNAL_ERROR;
        }
        for (int i = *nbStatements; i < (*nbStatements+50); i++){
            (*statements)[i]=(Tstate*)malloc(sizeof(Tstate));
        }
    }
    //printf("%d",*nbStatements);
    *(*statements)[*nbStatements]=*newStatement;
    *nbStatements = *nbStatements +1;               //pridam newstatement na nove miesto v poli
    return 0;
}
Tree** ASTcreateExpressions(int* nbExpressions){
    Tree** espressions=(Tree**)malloc(50*sizeof(Tree*));
    for (int i = 0; i < 49; i++){
        espressions[i]=(Tree*)malloc(sizeof(Tree));
    }
    *nbExpressions=0;

    return espressions;
}
/**
 * @brief vlozi zadane expression do zadaneho pola expressions
 * 
 * @param espressions 
 * @param nbExpressions 
 * @param newExpression 
 * @return int 
 */
int ASTaddToExpressions(Tree*** expressions, int* nbExpressions, Tree* newExpression){
    int sizeOfArray=0;                    //odvozdujem velkost pola
    if (*nbExpressions<50){
        sizeOfArray=50;
    }
    else{
        sizeOfArray=50*((*nbExpressions / 50) + 1);
    }

    if(*nbExpressions == (sizeOfArray)-1){           //-2 aby bol posledny znak vzdy null
        *expressions = (Tree**)realloc(*expressions, sizeof(Tree*)*(sizeOfArray+50));
        if (*expressions == NULL) return INTERNAL_ERROR;
        for (int i = *nbExpressions; i < (*nbExpressions+50); i++){
            (*expressions)[i]=(Tree*)malloc(sizeof(Tree));
        }
    }
    
    *(*expressions)[*nbExpressions]=*newExpression;
    *nbExpressions = *nbExpressions +1;               //pridam newstatement na nove miesto v poli
    return 0;
}
Token** ASTcreateTokenArray(int* nbTokens){
    Token** array=(Token**)malloc(50*sizeof(Token*));
    if(array==NULL) return NULL;
    for (int i = 0; i < 49; i++){
        array[i]=(Token*)malloc(sizeof(Token));
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
        for (int i = *nbTokens; i < (*nbTokens+50); i++){
            (*array)[i]=(Token*)malloc(sizeof(Token));
            if((*array)[i] == NULL) return INTERNAL_ERROR;
        }
    }
    *(*array)[*nbTokens]=*newToken;
    *nbTokens = *nbTokens +1;               //pridam newstatement na nove miesto v poli
    return 0;
}
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
        newLeaf->TStatement.definiton->state=(defineState*)malloc(sizeof(defineState));
        *newLeaf->TStatement.definiton->state=Empty;
        newLeaf->TStatement.definiton->id=(Token*)malloc(sizeof(Token));
        newLeaf->TStatement.definiton->data_type=(Token*)malloc(sizeof(Token));
        //newLeaf->TStatement.definiton->ExFc=(exfc*)malloc(sizeof(exfc));
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
        newLeaf->TStatement.assignment->IDs = ASTcreateTokenArray(newLeaf->TStatement.assignment->nbID);
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
        newLeaf->TStatement.functioncall->IDs = ASTcreateTokenArray(newLeaf->TStatement.functioncall->nbID);
        newLeaf->TStatement.functioncall->parameters = ASTcreateExpressions(newLeaf->TStatement.functioncall->nbParameters);
    }
    else if (type==ASTcondition){
        //-alokovat strukturu
        newLeaf->type=ASTcondition;
        newLeaf->TStatement.if_loop = (TIf_tree*)malloc(sizeof(TFunctioncall_tree));
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.if_loop->hasElse=(bool*)malloc(sizeof(bool));
        *(newLeaf->TStatement.if_loop->hasElse) = false;
        newLeaf->TStatement.if_loop->expression = (Tree*)malloc(sizeof(Tree));
        newLeaf->TStatement.if_loop->nbIfStatements = (int*)malloc(sizeof(int));
        *(newLeaf->TStatement.if_loop->nbIfStatements)=0;
        newLeaf->TStatement.if_loop->if_statements = ASTcreateStatements(newLeaf->TStatement.if_loop->nbIfStatements); 
    }
    else if (type==ASTreturn){
        //-alokovat strukturu
        newLeaf->type=ASTreturn;
        newLeaf->TStatement.FCreturn = (Treturn_tree*)malloc(sizeof(Treturn_tree));
        //--alokovat priestor pre Tokeny
        newLeaf->TStatement.FCreturn->nbexpressions = (int*)malloc(sizeof(int));
        *(newLeaf->TStatement.FCreturn->nbexpressions)=0;
        newLeaf->TStatement.FCreturn->expressions = ASTcreateExpressions(newLeaf->TStatement.FCreturn->nbexpressions);
    }

    return newLeaf;    
}
int ASTsaveToken(ASTstack* myStack, Token* myToken, saveType type){
    if (type==functionParams){
        if (myStack->head->statement->type==ASTfunction){
            ASTaddToTokenArray(ASTreturnFastArray(myStack,functionParams), ASTreturnFastArrayNB(myStack,functionParams), myToken);
        }
        else return INTERNAL_ERROR;
    }
    else if (type==functionReturnTypes){
        if (myStack->head->statement->type==ASTfunction){
            ASTaddToTokenArray(ASTreturnFastArray(myStack,functionReturnTypes), ASTreturnFastArrayNB(myStack,functionReturnTypes), myToken);
        }
        else return INTERNAL_ERROR;
    }
    else if (type==assigneIDs){
        if (myStack->head->statement->type==ASTassigne){
            ASTaddToTokenArray(ASTreturnFastArray(myStack,assigneIDs), ASTreturnFastArrayNB(myStack,assigneIDs), myToken);
        }
        else return INTERNAL_ERROR;
    }
    else if (type==functionCallParams){
        if (myStack->head->statement->type==ASTfunctionCall){
            ASTaddToTokenArray(ASTreturnFastArray(myStack,functionCallParams), ASTreturnFastArrayNB(myStack,functionCallParams), myToken);
        }
        else return INTERNAL_ERROR;
    }
    else if (type==functionCallIDs){
        if (myStack->head->statement->type==ASTfunctionCall){
            ASTaddToTokenArray(ASTreturnFastArray(myStack,functionCallIDs), ASTreturnFastArrayNB(myStack,functionCallIDs), myToken);
        }
        else return INTERNAL_ERROR;
    }
    else if(type==functionID){
        if(myStack->head->statement->type==ASTfunction){
            *(myStack->head->statement->TStatement.function->id)=*myToken;
        }
    }
    else if(type==definitionID){
        if(myStack->head->statement->type==ASTdefine){
            *(myStack->head->statement->TStatement.definiton->id)=*myToken;
        }
    }
    else if(type==definitionDataType){
        if(myStack->head->statement->type==ASTdefine){
            *(myStack->head->statement->TStatement.definiton->data_type)=*myToken;
        }
    }
    else if(type==functionCallName){
        if(myStack->head->statement->type==ASTfunctionCall){
            *(myStack->head->statement->TStatement.functioncall->functionName)=*myToken;
        }
    }
        
    return 0;
}
/**
 * @brief vrati cestu stackom k polu tokenov v danom type unie Tstate(len na zkratenie zapisu) 
 * 
 * @param myStack 
 * @param type 
 * @return Token*** 
 */
Token*** ASTreturnFastArray(ASTstack* myStack, saveType type){
    if(type==functionParams){
        return &(myStack->head->statement->TStatement.function->parameters);
    }
    else if(type==functionReturnTypes){
        return &(myStack->head->statement->TStatement.function->returnTypes);
    }
    else if(type==assigneIDs){
        return &(myStack->head->statement->TStatement.assignment->IDs);
    }
    else if(type==functionCallIDs){
        return &(myStack->head->statement->TStatement.functioncall->IDs);
    }
    /*else if(type==functionCallParams){
        return &(myStack->head->statement->TStatement.functioncall->parameters);
    }*/
    return NULL;
}
int* ASTreturnFastArrayNB(ASTstack* myStack, saveType type){
    if(type==functionParams){
        return myStack->head->statement->TStatement.function->nbParameters;
    }
    else if(type==functionReturnTypes){
        return myStack->head->statement->TStatement.function->nbReturntypes;
    }
    else if(type==assigneIDs){
        return myStack->head->statement->TStatement.assignment->nbID;
    }
    else if(type==functionCallIDs){
        return myStack->head->statement->TStatement.functioncall->nbID;
    }
    else if(type==functionCallParams){
        return myStack->head->statement->TStatement.functioncall->nbParameters;
    }
    return NULL;
}
void ASTprintStatement(Tstate* statement){
    if(statement->type==ASTglobal) printf("root\n");
    else if(statement->type==ASTfunction){
        printf("\033[1;33m");
        printf("function: %s\n", statement->TStatement.function->id->data.string);
        printf("\033[0m");
        if(*(statement->TStatement.function->nbParameters)!=0){
            for (int i = 0; i < *(statement->TStatement.function->nbParameters); i++){
                printf("    %d parameter: %s\n",i+1, statement->TStatement.function->parameters[i]->data.string);
            }
        }
        if(*(statement->TStatement.function->nbReturntypes)!=0){
            for (int i = 0; i < *(statement->TStatement.function->nbReturntypes); i++){
                printf("    %d returntype: %s\n",i+1, statement->TStatement.function->returnTypes[i]->data.string);
            }
        }
    }
    else if(statement->type==ASTcycle){
        printf("\033[1;36m");
        printf("    loop");
        printf("\033[0m");
        printf("\n        expression: ");
        printExpressionTree(statement->TStatement.while_loop->expression);
        printf("\n");
    }
    else if(statement->type==ASTdefine) {
        printf("\033[0;34m");
        printf("    define\n");
        printf("\033[0m");
        printf("        id: %s\n", statement->TStatement.definiton->id->data.string);
        printf("        dataType: %s\n", statement->TStatement.definiton->data_type->data.string);
        if (*(statement->TStatement.definiton->state)==Expression){
        
            printf("        expression: ");
            printExpressionTree(statement->TStatement.definiton->ExFc.expression);
            printf("\n");
        }
        else if(*(statement->TStatement.definiton->state)==FCcall){
            ASTprintStatement(statement->TStatement.definiton->ExFc.FCcall);
        }
    }
    else if(statement->type==ASTassigne){
        printf("\033[0;31m");
        printf("    assigment\n");
        printf("\033[0m");
        printf("        IDs: ");//vypis vsetky variables
        for (int i = 0; i < *statement->TStatement.assignment->nbID; i++){
            printf("%s, ",statement->TStatement.assignment->IDs[i]->data.string);
        }
        printf("\n        expression: ");
        for (int i = 0; i < *statement->TStatement.assignment->nbexpressions; i++){
            printExpressionTree(statement->TStatement.assignment->expressions[i]);
        }
        printf(", ");
    }
    else if(statement->type==ASTfunctionCall){
        printf("\033[0;32m");
        printf("    functionCall\n");
        printf("\033[0m");
        printf("        name: %s\n", statement->TStatement.functioncall->functionName->data.string);
        if(*(statement->TStatement.functioncall->nbID)!=0){
            printf("        IDs: ");//vypis vsetky variables
            for (int i = 0; i < *statement->TStatement.functioncall->nbID; i++){
                printf("%s, ",statement->TStatement.functioncall->IDs[i]->data.string);
            }
        }
        printf("\n        parameters: ");
        for (int i = 0; i < *statement->TStatement.functioncall->nbParameters; i++){
            printExpressionTree(statement->TStatement.functioncall->parameters[i]);
        }
    }
    else if (statement->type==ASTcondition)
    {
        printf("\033[1;36m");
        printf("    If\n");
        printf("\033[0m");
        printf("        expression: ");
        printExpressionTree(statement->TStatement.if_loop->expression);
        printf("\n");
    }
    else if(statement->type==ASTreturn){

        printf("\033[0;31m");
        printf("    return\n");
        printf("\033[0m");
        printf("        expression: ");
        for (int i = 0; i < *statement->TStatement.FCreturn->nbexpressions; i++){
            printExpressionTree(statement->TStatement.FCreturn->expressions[i]);
        }
        printf("\n");
    }
    int nb=0;
    Tstate* tmp;
    while(true){
        if (statement->type==ASTfunction){
            if (nb<*(statement->TStatement.function->nbStatements)){
                tmp=statement->TStatement.function->statements[nb];
            }
            else tmp=NULL;
        }
        else if (statement->type==ASTglobal){
            if (nb<*(statement->TStatement.root->nbStatements)){
                tmp=statement->TStatement.root->statements[nb];
            }
            else tmp=NULL;
        }
        else if (statement->type==ASTcycle){
            if (nb<*(statement->TStatement.while_loop->nbStatements)){
                tmp=statement->TStatement.while_loop->do_statement[nb];
            }
            else tmp=NULL;
        }
        else if (statement->type==ASTcondition){
            //tmp=NULL;
            if (nb<*(statement->TStatement.if_loop->nbIfStatements)){
                tmp=statement->TStatement.if_loop->if_statements[nb];
            }
            else {
                
                tmp=NULL;
            }
        }
        else if (statement->type==ASTdefine){
            tmp=NULL;
        }
        else if (statement->type==ASTassigne){
            tmp=NULL;
        }
        else if (statement->type==ASTfunctionCall){
            tmp=NULL;
        }
        else if (statement->type==ASTreturn){
            tmp=NULL;
        }
        
        nb=nb+1;
        if (tmp==NULL) break;
        ASTprintStatement(tmp);
    }
    if(statement->type==ASTglobal) printf("root end\n");
    else if(statement->type==ASTfunction) {printf("\033[1;33m"); printf("function end\n\n"); printf("\033[0m");}
    else if(statement->type==ASTcycle) {printf("\033[1;36m"); printf("    loop end\n"); printf("\033[0m");}
    else if(statement->type==ASTdefine) {printf("\033[0;34m");printf("    define end\n"); printf("\033[0m");}
    else if(statement->type==ASTassigne) {printf("\033[0;31m"); printf("\n    assigment end\n"); printf("\033[0m");}
    else if(statement->type==ASTfunctionCall) {printf("\033[0;32m"); printf("\n    functionCall end\n"); printf("\033[0m");}
    else if(statement->type==ASTcondition)   {printf("\033[1;36m"); printf("\n    condition end\n"); printf("\033[0m");}
    else if(statement->type==ASTreturn){printf("\033[0;31m"); printf("    return end\n"); printf("\033[0m");}
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
void ASTdeleteLastFromTree(ASTstack* myStack){
    if (myStack->head->next->statement->type==ASTglobal){
        *(myStack->head->next->statement->TStatement.root->nbStatements) = \
        *(myStack->head->next->statement->TStatement.root->nbStatements) - 1;
    }
    else if (myStack->head->next->statement->type==ASTfunction){
        *(myStack->head->next->statement->TStatement.function->nbStatements) = \
        *(myStack->head->next->statement->TStatement.function->nbStatements) - 1;
    }
    else if (myStack->head->next->statement->type==ASTcycle){
        *(myStack->head->next->statement->TStatement.while_loop->nbStatements) = \
        *(myStack->head->next->statement->TStatement.while_loop->nbStatements) - 1;
    }
    else if (myStack->head->next->statement->type==ASTcondition){
        if (myStack->head->next->statement->TStatement.if_loop->hasElse==false){
            *(myStack->head->next->statement->TStatement.if_loop->nbIfStatements) = \
            *(myStack->head->next->statement->TStatement.if_loop->nbIfStatements) - 1;
        }
        else{
            *(myStack->head->next->statement->TStatement.if_loop->nbElseStatements) = \
            *(myStack->head->next->statement->TStatement.if_loop->nbElseStatements) - 1;
        }
    }
}
void ASTinBuildArrayInit(inbuild* array){
    for (int i = 0; i < 8; i++){
        array[i]=empty;
    }
}
void ASTinBuildUsed(ASTtree* tree, inbuild FC){
    for (int i = 0; i < 8; i++){
        if (tree->tree->TStatement.root->UsedInBuild[i]==empty){
            tree->tree->TStatement.root->UsedInBuild[i]=FC;
            break;
        }
        else if(tree->tree->TStatement.root->UsedInBuild[i]==FC) break;
    }
}
bool ASTisInBuildUsed(ASTtree* tree, inbuild FC){
    for (int i = 0; i < 8; i++){
        if (tree->tree->TStatement.root->UsedInBuild[i]==empty) return false;
        else if(tree->tree->TStatement.root->UsedInBuild[i]==FC) return true;
    }
}
void ASTprintInBuild(ASTtree* tree){
    printf("\nUsed InBuild------------------------------------------------------\n\n");
    for (int i = 0; i < 8; i++){
        if (tree->tree->TStatement.root->UsedInBuild[i]!=empty){
            printf("%d ",tree->tree->TStatement.root->UsedInBuild[i]);
        }
        else break;
        
    }
}
void printExpressionTree(Tree *exprtree){
    if (exprtree->Data->type == Integer){
        printf("%i ", exprtree->Data->data.integer);
    }
    else if (exprtree->Data->type == Number){
        printf("%f ", exprtree->Data->data.number);
    }
    else if (exprtree->Data->type == String){
        printf("%s ", exprtree->Data->data.string);
    }

    else if (exprtree->Data->type == Identifier){
        printf("%s ", exprtree->Data->data.string);
    }

    else if (exprtree->Data->type == Sizeof){
        printf("%s ", exprtree->Data->data.string);
        printExpressionTree(exprtree->attr.unary.child);
    }

    else if (strcmp(exprtree->Data->data.string, "nil") == 0){
        printf("nil ");
    } 

    else if (exprtree->Data->type == Plus || \
            exprtree->Data->type == Minus || \
            exprtree->Data->type == Multiplication || \
            exprtree->Data->type == Division_integer || \
            exprtree->Data->type == Division || \
            exprtree->Data->type == Concatenation || \
            exprtree->Data->type == Less || \
            exprtree->Data->type == More || \
            exprtree->Data->type == Less_equal || \
            exprtree->Data->type == More_equal || \
            exprtree->Data->type == Is_equal || \
            exprtree->Data->type == Not_equal || \
            exprtree->Data->type == Assign){
        printExpressionTree(exprtree->attr.binary.left);
        printf("%s ", exprtree->Data->data.string);
        printExpressionTree(exprtree->attr.binary.right);
    }
}

