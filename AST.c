
#include "AST.h"

/*podla typu prejde cestu od stack head po statements blok*/
Tstate*** ASTreturnFastST(ASTstack* myStack){
    statementType Type=myStack->head->statement->type;
    if (Type==ASTfunction){
        return &(myStack->head->statement->TStatement.function->statements);
    }
    else if( Type==ASTglobal){
        return &(myStack->head->statement->TStatement.root->statements);
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
int ASTaddToStatements(Tstate*** statements, int* nbStatements, Tstate* newStatement){
    int sizeOfArray=0;                    //odvozdujem velkost pola
    if (*nbStatements<50){
        sizeOfArray=50;
    }
    else{
        sizeOfArray=50*((*nbStatements / 50) + 1);
    }
    
    if(*nbStatements == (sizeOfArray)-2){           //-2 aby bol posledny znak vzdy null
        *statements = (Tstate**)realloc(*statements, sizeof(Tstate*)*(sizeOfArray+50));
        for (int i = 1; i < 50; i++){
            statements[*nbStatements+i]=NULL;
        }
        if (*statements == NULL){
            return INTERNAL_ERROR;
        }
    }
    
    (*statements)[*nbStatements]=newStatement;
    *nbStatements = *nbStatements +1;               //pridam newstatement na nove miesto v poli
    return sizeOfArray;
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
/*(stackpop) dorobit uvolnovanie veci ak bude cas*/
void ASTendStatement(ASTstack *myStack){
    ASTstackElement* tmp;
    if (myStack->head!=NULL){
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
}
/*int ASTnewElementInit(Tstate* newElement, statementType Type){
    if (Type==ASTfunction){
        return ASTcreateStatements(&(newElement->TStatement.function->statements));
    }    
    return 0;
}*/
/*void ASTprintTree(TRoot* tree){
    int nb=0;
    Tstate* tmp;
    while(true){
        if (tree->global_state[nb]==ASTfunction){
            tmp=tree->global_state[nb]->TStatement.function->statements[nb];
        }

        if (tmp==NULL) break;
        ASTprintStatement(tmp);
        nb=nb+1;
    }
}*/
Tstate* ASTcreateLeaf(statementType type){
    Tstate* newLeaf=(Tstate*)malloc(sizeof(Tstate));
    if(type==ASTglobal){
        newLeaf->type=ASTglobal;
        newLeaf->TStatement.root = (root*)malloc(sizeof(root));
        newLeaf->TStatement.root->nbStatements = (int*)malloc(sizeof(int));
        (*newLeaf->TStatement.root->nbStatements)=0;
        newLeaf->TStatement.root->statements = ASTcreateStatements(newLeaf->TStatement.root->nbStatements);
    }
    else if (type==ASTfunction){
        newLeaf->type=ASTfunction;
        newLeaf->TStatement.function = (TFunction_tree*)malloc(sizeof(TFunction_tree));
        newLeaf->TStatement.function->nbStatements = (int*)malloc(sizeof(int));
        (*newLeaf->TStatement.function->nbStatements)=0;
        newLeaf->TStatement.function->statements = ASTcreateStatements(newLeaf->TStatement.function->nbStatements);
    }
    
    return newLeaf;
    
}
void ASTprintStatement(Tstate* statement){
    if(statement->type==ASTglobal) printf("root\n");
    else if(statement->type==ASTfunction) printf("function\n");
    int nb=0;
    Tstate* tmp;
    while(true){
        if (statement->type==ASTfunction){
            tmp=statement->TStatement.function->statements[nb];
        }
        else if (statement->type==ASTglobal){
            tmp=statement->TStatement.root->statements[nb];
        }
        nb=nb+1;
        if (tmp==NULL) break;
        ASTprintStatement(tmp);
    }
    if(statement->type==ASTglobal) printf("root end\n");
    else if(statement->type==ASTfunction) printf("function end\n");
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