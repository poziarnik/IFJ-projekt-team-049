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
        
    //   <|>  .. +|- *|/  #   (   )   i   $
        {'R','L','L','L','L','L','R','L','R'}, // < <= > >= == ~=    S
        {'R','L','L','L','L','L','R','L','R'}, // ..                  
        {'R','R','R','L','L','L','R','L','R'}, // + -                T
        {'R','R','R','R','L','L','R','L','R'}, // * / //              
        {'R','R','R','R','E','L','R','L','R'}, // #                  A
        {'L','L','L','L','L','L','I','L','E'}, // (                  
        {'R','R','R','R','R','E','R','E','R'}, // )                  C
        {'R','R','R','R','R','E','R','E','R'}, // i
        {'L','L','L','L','L','L','E','L','E'}  // $                  K
    };
                                               
    TStack *Stack = (TStack*)malloc(sizeof(TStack));
    if (Stack == NULL) {
        return INTERNAL_ERROR;
    }
    bool END = false;
    Token *tmp;
    Stack_push(Stack, ELSE, NULL);

    do{
        switch (table[Stack_first_nonterm(Stack)][table_input_symbol(MyToken->type)]){

        case 'L':
        
            puts("op expand");
            if (Stack->top->Item == 'E'){
                Stack_push_beforeNonterm(Stack);
                Stack_push(Stack, table_input_symbol(MyToken->type), MyToken);
            }
            else{
                Stack_push(Stack, '<', NULL);
                Stack_push(Stack, table_input_symbol(MyToken->type), MyToken); 
            }
            tokenScan(stdin, list, MyToken);
            break;
      
        case 'R':
            if (Stack->top->Item == PLUS_MINUS || Stack->top->Item == MULTIPLICATION_DIVISION_INTDIV){
                return SYNTAX_ERROR;
            }
            
            reduce_by_rule(Stack, MyToken);
            puts("op reduce");
            
            
            break;
    
        case 'I':
            puts("op equals");
            reduce_by_rule(Stack, MyToken);
            
            // if (stack1.Item == RIGHTBRACKET && stack2.Item == NOTERM && stack3.Item == LEFTBRACKET)
            // {
            //     Stack_push(Stack, stack2.Item, stack3.token);
            // }
            
            
            break;

        case 'E':
        puts("op end");
            END = true;            
            break;
        }  

        

    } while (!END);
    if (Stack->top->Item == NOTERM && Stack_first_nonterm(Stack) == ELSE){
        return 0;
    }
    return SYNTAX_ERROR;
}


int table_input_symbol(Token_type type){
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
}

int reduce_by_rule(TStack *Stack, Token *token){
    TElement *stack_1;
    TElement *stack_2;
    TElement *stack_3;
    Token *tmp;
    if (Stack_first_nonterm(Stack) == DATA){
        tmp = Stack->top->token;
        Stack_pop_till_bracket(Stack);
        Stack_push(Stack, NOTERM, tmp);
    }
    else if (Stack_first_nonterm(Stack) == PLUS_MINUS ||  \
        (Stack_first_nonterm(Stack) == MULTIPLICATION_DIVISION_INTDIV)  || \
        (Stack_first_nonterm(Stack) == LESS_MORE_EQUAL_NOTEQUAL)){
        stack_1 = Stack->top;
        Stack_pop(Stack);
        stack_2 = Stack->top;
        Stack_pop(Stack);
        stack_3 = Stack->top;
        Stack_pop(Stack);
        Stack_pop(Stack);
        

        Stack_push(Stack, NOTERM, NULL);   
    }
    else if (Stack_first_nonterm(Stack) == LEFTBRACKET){
        stack_1 = Stack->top;
        Stack_pop(Stack);
        stack_2 = Stack->top;
        Stack_pop(Stack);
        stack_3 = Stack->top;
        Stack_pop(Stack);
        Stack_push(Stack, NOTERM, NULL);  
    }
    else if (Stack_first_nonterm(Stack) == SIZEOF){
        stack_1 = Stack->top;
        Stack_pop(Stack);
        stack_2 = Stack->top;
        Stack_pop(Stack);
        Stack->top->Item = NOTERM;
        Stack->top->token = NULL;
    }
    stack_1 = NULL;
    stack_2 = NULL;
    stack_3 = NULL;
    return 0;
}

int reduce_brackets(TStack *Stack, Token *token){
    TElement *stack1;
    TElement *stack2;
    TElement *stack3;
    stack1 = Stack->top;
    Stack_pop(Stack);
    stack2 = Stack->top;
    Stack_pop(Stack);
    stack3 = Stack->top;
    Stack->top->Item = NOTERM;
    Stack->top->token = NULL;

    return 1;
}