#include "MyStackTree.h"


void Stack_init(TStack *Stack){
    Stack->top = NULL;
    
}

void Stack_push(TStack *Stack, int newItem, Token *token){
    TElement *new = (TElement*)malloc(sizeof(TElement));
    if (new == NULL){
        return;
    }
    new->Item = newItem;
    new->token = token;
    new->next = Stack->top;
    Stack->top = new;   
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

void tree_init(Tnode **tree){
    *tree = NULL;
}

int Stack_first_nonterm(TStack *stack){
    for (TElement *tmp = stack->top; tmp != NULL; tmp = tmp->next){
        if (tmp->Item < 9){
            return tmp->Item;
        }
    }
    return 0;
}

void Stack_push_beforeNonterm(TStack *stack){
    TElement *tmp;
    tmp = stack->top;
    stack->top->Item = '<';
    stack->top->token = NULL;
    Stack_push(stack, tmp->Item, tmp->token);
    free(tmp);
    tmp = NULL;
}

void treeInit(Tree **tree){
    *tree = NULL;
}

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
