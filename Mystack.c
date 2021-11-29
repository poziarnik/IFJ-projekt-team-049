#include "MyStackTree.h"


void Stack_init(TStack *Stack){
    Stack->top = NULL;
}

int Stack_push(TStack *Stack, int newItem, Token *token){
    TElement *new = (TElement*)malloc(sizeof(TElement));
    if (new == NULL){
        return INTERNAL_ERROR;
    }

    Tree *newTree = (Tree*)malloc(sizeof(Tree)); 
    if (newTree == NULL){
        return INTERNAL_ERROR;
    }

    if(token != NULL){
        Token *newToken = (Token*)malloc(sizeof(Token));
        if (newToken == NULL){
            return INTERNAL_ERROR;
        }
        *newToken = *token;
        newTree->Data = newToken; 
        
    }
    else{
        newTree->Data = NULL; 
    }
    
    new->Item = newItem;
    new->tree = newTree;
    new->next = Stack->top;
    Stack->top = new;
    return 0;
}


void Stack_pop(TStack *Stack){
    TElement *tmp = Stack->top;
    Stack->top = Stack->top->next;
    free(tmp);
}

void Stack_pop_till_bracket(TStack *Stack){
    while (Stack->top->Item != '<'){
        Stack_pop(Stack);
    }
    if (Stack->top->Item == '<'){
        Stack_pop(Stack);
    }    
}

int Stack_first_nonterm(TStack *stack){
    for (TElement *tmp = stack->top; tmp != NULL; tmp = tmp->next){
        if (tmp->Item < NOTERM){
            return tmp->Item;
        }
    }
    return 0;
}

void Stack_push_beforeNonterm(TStack *stack){
    TElement *tmp;
    tmp = stack->top;
    stack->top->Item = '<';
    stack->top->tree->Data = NULL;
    Stack_push(stack, tmp->Item, tmp->tree->Data);
    tmp = NULL;
}

void treeInit(Tree **tree){
    *tree = NULL;
}


/*
Tree *treeInsert_BinaryOperator(Tree **tree, TElement *Operator, TElement *Data1, TElement *Data2){
    Tree *newTree = (Tree*)malloc(sizeof(Tree));
    if (newTree == NULL){
        return NULL; //TODO
    }
    
    newTree->Data = Operator->token;
    newTree->attr.binary.left->Data = Data1->token;
    newTree->attr.binary.right->Data = Data2->token;

    return newTree;
}
*/

/*
Tree *tree_insert_UnaryOperator(Tree **tree, TElement *Operator, TElement *Data){
    Tree *newTree = (Tree*)malloc(sizeof(Tree));
    if (newTree == NULL){
        return NULL; //TODO
    }
    
    
    newTree->Data = Operator->token;
    newTree->attr.unary.child->Data = Data->token;

    printf("%i", (*tree)->Data->data.integer);

    return newTree;
}
*/
