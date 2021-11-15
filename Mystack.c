#include "Mystack.h"


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



