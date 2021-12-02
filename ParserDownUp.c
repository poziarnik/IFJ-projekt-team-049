#include "ParserDownUp.h"


#define SCAN_TOKEN \
    status = tokenScan(stdin, list, MyToken); \
    if (status==LEXICAL_ERROR ) return LEXICAL_ERROR;


int expressionCheck(Token* MyToken, TokenList* list, Tree *expression){
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
        {'R','R','R','R','R','E','R','E','R'}, // i
        {'L','L','L','L','L','L','E','L','E'}  // $                  K
    };
                                               
    TStack *Stack = (TStack*)malloc(sizeof(TStack));
    if (Stack == NULL) {
        return INTERNAL_ERROR;
    }
    Stack_init(Stack);
    bool END = false;
    
    Stack_push(Stack, ELSE, NULL);
    
    TElement *stackHelp;
    
    
    do{
        switch (table[Stack_first_nonterm(Stack)][table_input_symbol(MyToken)]){
            
        case 'L':
            puts("op expand");
            if(Stack->top->Item == NOTERM){
                
                if (table_input_symbol(MyToken) == DATA){
                    reduce_by_rule(Stack, MyToken);
                    return 1;
                }

                
                stackHelp = stack_pop_nofree(Stack);
                Stack_push(Stack, '<', NULL);
                stackHelp->Item = NOTERM;
                Stack_Push_Element(Stack, stackHelp);
                Stack_push(Stack, table_input_symbol(MyToken), MyToken);
                
            }
            else{
                Stack_push(Stack, '<', NULL);
                Stack_push(Stack, table_input_symbol(MyToken), MyToken);
            }
            

            // if (Stack->top->tree->Data->type == Plus){
            //     printf("%s\n", Stack->top->tree->Data->data.string);
            // }
            // else if (Stack->top->tree->Data->type == Integer){
            //     printf("%i\n", Stack->top->tree->Data->data.integer);
            // }
            
            
            SCAN_TOKEN
            break;

      
        case 'R':
            puts("op reduce");
            
            status = reduce_by_rule(Stack, MyToken);
            if (status != 0){
                return status;
            }

            
    
            break;
        case 'I':
            puts("op equals");

            status = reduce_by_rule(Stack, MyToken);
            if (status != 0){
                return status;
            }
            
            SCAN_TOKEN;
            
            break;

        case 'E':
            puts("op end");
            END = true;
            break;

        case 'U':
            while (Stack->top->Item != NOTERM || Stack->top->next->Item != ELSE){
                status = reduce_by_rule(Stack, MyToken);
            }
            if (status != 0){
                return status;
            }
            END = true;
            break;
        } 

    } while (!END);
    
    
    

    
    if (Stack->top->Item == NOTERM && Stack->top->next->Item == ELSE){
        *expression = *Stack->top->tree;
        return PROGRAM_OK;
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

int reduce_by_rule(TStack *Stack, Token *MyToken){

    TElement *main, *left, *right, *bracket, *child;
    
    //Pravidlo |<i -> E|
    if (Stack_first_nonterm(Stack) == DATA){
        main = stack_pop_nofree(Stack);
        main->Item = NOTERM;
        Stack_pop(Stack);  // potom vyhodim pomocnu zatvorku <
       
        Stack_Push_Element(Stack, main);
        main = NULL;
    }



    // pravidlo |<E + E -> E|
    else if (Stack_first_nonterm(Stack) == PLUS_MINUS ||  \
        (Stack_first_nonterm(Stack) == MULTIPLICATION_DIVISION_INTDIV)  || \
        (Stack_first_nonterm(Stack) == LESS_MORE_EQUAL_NOTEQUAL) || \
        (Stack_first_nonterm(Stack) == CONCATENATION)){
            //ak je na stacku prvy TERM plus, minus, krat, deleno, ...
            //kontrolujem ci prvy na stacku je NETRMINAL



        right = stack_pop_nofree(Stack);
        if (right->Item != NOTERM){  //ak na vrchole nie je E 
            return SYNTAX_ERROR;
        }

        main = stack_pop_nofree(Stack);
        if (main->Item != PLUS_MINUS && main->Item != MULTIPLICATION_DIVISION_INTDIV && \
            main->Item != LESS_MORE_EQUAL_NOTEQUAL && main->Item != Concatenation){
            // po NETERMINALY musi prist binarny operator
            return SYNTAX_ERROR;
        }
            
        left = stack_pop_nofree(Stack);
        if (left->Item != NOTERM){  //ak na vrchole nie je E 
            return SYNTAX_ERROR;
        }

        //vyhodim < zo stacku
        Stack_pop(Stack);

        //ako hlavny koren necham Element s binarnym operatorom, ale zmenim jeho nazov na NOTERM
        main->Item = NOTERM;
            
        //alokujem jeho podstromy a priradim donho NETERMINALY
        main->tree->attr.binary.left = (Tree*)malloc(sizeof(Tree));
        main->tree->attr.binary.left = left->tree;

        main->tree->attr.binary.right = (Tree*)malloc(sizeof(Tree));
        main->tree->attr.binary.right = right->tree;

        //pushnem na Stack koren
        Stack_Push_Element(Stack, main);

        free(right);
        free(left);   
    }

    else if (Stack_first_nonterm(Stack) == LEFTBRACKET){
        bracket = stack_pop_nofree(Stack);

        if (bracket->Item != NOTERM){
            return SYNTAX_ERROR;
        }
        Stack_pop(Stack);
        Stack_pop(Stack);

        Stack_Push_Element(Stack, bracket);
    }

    else if (Stack_first_nonterm(Stack) == SIZEOF){
        child = stack_pop_nofree(Stack);
        if (child->Item != NOTERM){
            return SYNTAX_ERROR;
        }

        main = stack_pop_nofree(Stack);
        if (main->Item != SIZEOF){
            return SYNTAX_ERROR;
        }

        Stack_pop(Stack);

        main->tree->attr.unary.child = (Tree*)malloc(sizeof(Tree));
        main->tree->attr.unary.child = child->tree;
        
        main->Item = NOTERM;

        Stack_Push_Element(Stack, main);
    }

    
        


    
    return PROGRAM_OK;
}