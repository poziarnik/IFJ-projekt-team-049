#include "ParserDownUp.h"
#define NUMBER_OF_RULES 4

#define SCAN_TOKEN \
    status = tokenScan(stdin, list, MyToken); \
    if (status==1) return 1; \
    if (status==10) return 10


int compare(Token* MyToken, TokenList* list){
    int status;
    int table[9][9]={

        // I       N       P       U       T

        {'R','L','L','L','L','L','R','L','R'}, // < <= > >= == ~=    S
        {'R','L','L','L','L','L','R','L','R'}, // ..                  
        {'R','R','R','L','L','L','R','L','R'}, // + -                T
        {'R','R','R','R','L','L','R','L','R'}, // * / //              
        {'R','R','R','R','E','L','R','L','R'}, // #                  A
        {'L','L','L','L','U','L','I','L','E'}, // (                  
        {'R','R','R','R','U','E','R','E','R'}, // )                  C
        {'R','R','R','R','U','E','R','E','R'}, // i
        {'L','L','L','L','U','L','E','L','E'}  // $                  K
    };
                                               
    TStack *Stack = (TStack*)malloc(sizeof(TStack));
    if (Stack == NULL){
        return 99;
    }
    bool END = false;
    Stack_push(Stack, ELSE, NULL);
    while (END != true){

        full_Stack(Stack, MyToken, table);
        if (MyToken->type == 23)
        {
            END = true;
        }
        tokenScan(stdin, list, MyToken);
        
    }
    printf("%i", line_table(MyToken->type));
    printf("%i\n\n", colomn_table(Stack));
    while (Stack->top != NULL){
        printf("%i\n", Stack->top->Item);
        Stack->top = Stack->top->next;
    }
    
    
    
    
    
}


int line_table(Token_type type){
    switch (type){

        case Less:
        case Less_equal:
        case More:
        case More_equal:
        case Is_equal:
        case Not_equal:
            return LESS_MORE_EQUAL_NOTEQUAL;

        case Concatenation:
            return CONCATENATION;

        case Plus:
        case Minus:
            return PLUS_MINUS;

        case Multiplication:
        case Division:
        case Division_integer:
            return MULTIPLICATION_DIVISION_INTDIV;

        case Sizeof:
            return SIZEOF;

        case L_bracket:
            return LEFTBRACKET;

        case R_bracket:
            return RIGHTBRACKET;
        
        case Integer:
        case Number:
        case String:
            return DATA;

        default:
            return ELSE;
    }
    return 99;
}

int colomn_table(TStack *Stack){
    if (Stack->top->Item == 'E'){
        return Stack->top->next->Item;
    }
    
    return Stack->top->Item;
}
  
void full_Stack(TStack *Stack, Token *token, int table[9][9]){
    TElement *tmp;
    switch (table[colomn_table(Stack)][line_table(token->type)]){
    case 'L':
        if (Stack->top->Item == 'E'){
            tmp = Stack->top;
            Stack_pop(Stack);
            Stack_push(Stack, '<', NULL);
            Stack_push(Stack, tmp->Item, tmp->token);
            tmp = NULL;
        }
        
        Stack_push(Stack, '<', NULL);
        Stack_push(Stack, line_table(token->type), token);
        break;

    case 'R': 
        tmp = Stack->top;
        Stack_pop_till_bracket(Stack);
        Stack_push(Stack, 'E', tmp->token);
        tmp = NULL;
        break;
    }
    

}
