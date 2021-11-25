#include "ParserDownUp.h"
#define NUMBER_OF_RULES 4

#define SCAN_TOKEN \
    status = tokenScan(stdin, list, MyToken); \
    if (status==1 ) return 1; \
    else if(status == 10) return 0;


int expressionCheck(Token* MyToken, TokenList* list){
    int status = 0;
    int table[9][9]={

        // I       N       P       U       T
        
    //   <|>  .. +|- *|/  #   (   )   i   $
        {'E','L','L','L','L','L','R','L','R'}, // < <= > >= == ~=    S
        {'R','L','L','L','L','L','R','L','R'}, // ..                  
        {'R','R','R','L','L','L','R','L','R'}, // + -                T
        {'R','R','R','R','L','L','R','L','R'}, // * / //              
        {'R','R','R','R','E','L','R','L','R'}, // #                  A
        {'L','L','L','L','L','L','I','L','E'}, // (                  
        {'R','R','R','R','R','E','R','E','R'}, // )                  C
        {'R','R','R','R','R','E','R','U','R'}, // i
        {'L','L','L','L','L','L','E','L','E'}  // $                  K
    };
                                               
    TStack *Stack = (TStack*)malloc(sizeof(TStack));
    if (Stack == NULL) {
        return INTERNAL_ERROR;
    }
    Stack_init(Stack);
    bool END = false;
    Stack_push(Stack, ELSE, NULL);
    TElement stackHelp;
    
    do{
        switch (table[Stack_first_nonterm(Stack)][table_input_symbol(MyToken)]){
            
        case 'L':
            if(Stack->top->Item == NOTERM){
                
                
                if (table_input_symbol(MyToken) == DATA){
                    reduce_by_rule(Stack);
                    return 1;
                }

                stackHelp = *Stack->top;
                Stack_pop(Stack);
                Stack_push(Stack, '<', NULL);
                Stack_push(Stack, NOTERM, (&stackHelp)->tree->Data);
                Stack_push(Stack, table_input_symbol(MyToken), MyToken);
            }
            else{
                Stack_push(Stack, '<', NULL);
                Stack_push(Stack, table_input_symbol(MyToken), MyToken);
            }
            
            
            status = tokenScan(stdin, list, MyToken);
            
            break;

      
        case 'R':
            //puts("op reduce");
            
            status = reduce_by_rule(Stack);
            if (status != 0){
                return status;
            }
            break;
    
        case 'I':
            //puts("op equals");

            status = reduce_by_rule(Stack);
            if (status != 0){
                return status;
            }


            status = tokenScan(stdin, list, MyToken);
            break;

        case 'E':
            END = true;
            break;

        case 'U':
            
            reduce_by_rule(Stack);
            END = true;
        }



         
        

    } while (!END);
    
    /*puts("---------------------");
    puts("");
    printf("%s\n", Stack->top->tree->Data->data.string);
    puts("");
    puts("---------------------");*/

    printf("%i",Stack->top->tree->Data->data.integer);
    
    if (Stack->top->Item == NOTERM && Stack->top->next->Item == ELSE){
                return 0;
    }
    return SYNTAX_ERROR;
}


int table_input_symbol(Token *MyToken){
    if (MyToken->type == Keyword){
        if (strcmp(MyToken->data.string, "nil") == 0){
            return DATA;
        }  
    }

    switch (MyToken->type){

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
        case Identifier:
            return DATA;

        default:
            return ELSE;
    }
}

int reduce_by_rule(TStack *Stack){
    TElement stack_1;
    TElement stack_2;
    TElement stack_3;

    if (Stack_first_nonterm(Stack) == DATA){
        stack_1 = *Stack->top;
        Tree *newTree = (Tree*)malloc(sizeof(Tree));
        if (newTree == NULL){
            return INTERNAL_ERROR;
        }
        
        newTree->Data = stack_1.tree->Data;
        Stack_pop(Stack);
        Stack->top->Item = NOTERM;
        *Stack->top->tree = *newTree;
    }


    else if (Stack_first_nonterm(Stack) == PLUS_MINUS ||  \
        (Stack_first_nonterm(Stack) == MULTIPLICATION_DIVISION_INTDIV)  || \
        (Stack_first_nonterm(Stack) == LESS_MORE_EQUAL_NOTEQUAL) || \
        (Stack_first_nonterm(Stack) == CONCATENATION)){
            
            if (Stack->top->Item != NOTERM){
                return SYNTAX_ERROR;
            }
            stack_1 = *Stack->top;
            Stack_pop(Stack);


            if (Stack->top->Item != PLUS_MINUS && \
                Stack->top->Item != MULTIPLICATION_DIVISION_INTDIV && \
                Stack->top->Item != LESS_MORE_EQUAL_NOTEQUAL && \
                Stack->top->Item != CONCATENATION){
                return SYNTAX_ERROR;
            }
            stack_2 = *Stack->top;
            Stack_pop(Stack);

            
            if (Stack->top->Item != NOTERM){
                return SYNTAX_ERROR;
            }
            stack_3 = *Stack->top;
            Stack_pop(Stack);
            

            if (Stack->top->Item != '<'){
                return SYNTAX_ERROR;
            }
            Tree *newTree = (Tree*)malloc(sizeof(Tree));
            if (newTree == NULL){
                return INTERNAL_ERROR;
            }
            newTree->Data = stack_2.tree->Data;
            newTree->attr.binary.right = stack_1.tree;
            newTree->attr.binary.left = stack_3.tree;

            Stack->top->Item = NOTERM;
            Stack->top->tree = newTree;
    }


    else if (Stack_first_nonterm(Stack) == LEFTBRACKET){
        stack_1 = *Stack->top;
        if (Stack->top->Item != NOTERM){
            return INTERNAL_ERROR;
        }
        Stack_pop(Stack);


        if (Stack->top->Item != LEFTBRACKET){
            return INTERNAL_ERROR;
        }
        Stack_pop(Stack);


        Stack->top->Item = NOTERM;
        Stack->top->tree = stack_1.tree;  
    }


    else if (Stack_first_nonterm(Stack) == SIZEOF){
        if (Stack->top->Item != NOTERM){
            return SYNTAX_ERROR;
        }
        stack_1 = *Stack->top;
        Stack_pop(Stack);


        if (Stack->top->Item != SIZEOF){
            return SYNTAX_ERROR;
        }
        stack_2 = *Stack->top;
        Stack_pop(Stack);

        Tree *newTree = (Tree*)malloc(sizeof(Tree));
        if(newTree == NULL){
            return INTERNAL_ERROR;
        }

        newTree->Data = stack_2.tree->Data;
        newTree->attr.unary.child = stack_1.tree;

        Stack->top->Item = NOTERM;
        Stack->top->tree = newTree;
    }
    return 0;
}


