#include "MyStackTree.h"


void Stack_init(TStack *Stack){
    Stack->top = NULL;
}

int Stack_push(TStack *Stack, int newItem, Token *token){
    
    TElement *new = (TElement*)malloc(sizeof(TElement));
    if (new == NULL){
        return INTERNAL_ERROR;
    }

    new->tree = (Tree*)malloc(sizeof(Tree)); 
    if (new->tree == NULL){
        return INTERNAL_ERROR;
    }

    if(token != NULL){
        new->tree->Data = (Token*)malloc(sizeof(Token));
        if (new->tree->Data == NULL){
            return INTERNAL_ERROR;
        }
        *new->tree->Data = *token; 
    }
    else{
        new->tree->Data = NULL; 
    }

    TElement *tmp = Stack->top; 
    new->Item = newItem;
    new->next = tmp;
    Stack->top = new;



    
    return 0;
}

void Stack_Push_Element(TStack *Stack, TElement *Element){
    TElement *tmp = Stack->top;
    //printf("push element tmp --> %p\n", tmp);
    Stack->top = Element;
    Stack->top->next = tmp;
    //printf("push element top next --> %p\n", Stack->top->next);
}


TElement *stack_pop_nofree(TStack *stack){
    // kontrola ci je stack prazdny
    if(stack->top == NULL) return NULL;

    TElement *tmp = stack->top; // do tmp ulozim top
    stack->top = tmp->next; // novy top bude tmp->next
    //tmp->next = NULL; // z tmp zrusis odkaz na dalsi prvok 
    return tmp; // vratis ukazatel na tmp
}

void Stack_pop(TStack *Stack){
    TElement *tmp = Stack->top;
    Stack->top = Stack->top->next;
    //tmp->next = NULL;
}


int Stack_first_nonterm(TStack *stack){
    for (TElement *tmp = stack->top; tmp != NULL; tmp = tmp->next){
        if (tmp->Item < NOTERM){
            return tmp->Item;
        }
    }
    return -1;
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

TElement Stack_top(TStack *stack){
    return *stack->top;
}

void freeExprTree(Tree *exprTree){
    if (exprTree->Data->type == Integer || exprTree->Data->type == String || exprTree->Data->type == Number){
        free(exprTree->Data);
        free(exprTree);
    }
    else if (exprTree->Data->type == Plus){
        freeExprTree(exprTree->attr.binary.right);
        freeExprTree(exprTree->attr.binary.left);
    }
    else if (exprTree->Data->type == Sizeof){
        freeExprTree(exprTree->attr.unary.child);
    }
}