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
        {'R','R','R','R','R','E','R','U','R'}, // i
        {'L','L','L','L','L','L','E','L','E'}  // $                  K
    };
                                               
    TStack *Stack = (TStack*)malloc(sizeof(TStack));
    if (Stack == NULL) {
        return INTERNAL_ERROR;
    }
    Stack_init(Stack);
    bool END = false;
    
    status = Stack_push(Stack, ELSE, NULL);
    if (status != PROGRAM_OK){
        return INTERNAL_ERROR;
    }
    
    TElement *stackHelp = NULL;
    
    do{
        switch (table[Stack_first_nonterm(Stack)][table_input_symbol(MyToken)]){
            
        case 'L':
            // puts("op expand");
            if (Stack->top->Item == NOTERM && table_input_symbol(MyToken) == DATA){
                while (Stack->top->Item != NOTERM || Stack->top->next->Item != ELSE){
                status = reduce_by_rule(Stack, MyToken);
            }
                END = true;
            }
            

            else if(Stack->top->Item == NOTERM){
                
                if (table_input_symbol(MyToken) == DATA){
                    status = reduce_by_rule(Stack, MyToken);
                    if (status != PROGRAM_OK){
                        return INTERNAL_ERROR;
                    }
                    
                }
                
                stackHelp = stack_pop_nofree(Stack);
                status = Stack_push(Stack, '<', NULL);
                if (status != PROGRAM_OK){
                    return status;
                }
                
                stackHelp->Item = NOTERM;
                Stack_Push_Element(Stack, stackHelp);

                status = Stack_push(Stack, table_input_symbol(MyToken), MyToken);
                if (status != PROGRAM_OK){
                    return status;
                }
                
            }
            else{
                status = Stack_push(Stack, '<', NULL);
                if (status != PROGRAM_OK){
                    return status;
                }

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
            // puts("op reduce");
            
            status = reduce_by_rule(Stack, MyToken);
            if (status != 0){
                return status;
            }

            
    
            break;
        case 'I':
            // puts("op equals");

            status = reduce_by_rule(Stack, MyToken);
            if (status != 0){
                return status;
            }
            
            SCAN_TOKEN;
            
            break;

        case 'E':
            // puts("op end");
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
            main->Item != LESS_MORE_EQUAL_NOTEQUAL && main->Item != CONCATENATION){
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
        if (main->tree->attr.binary.left == NULL){
            return INTERNAL_ERROR;
        }
        main->tree->attr.binary.left = left->tree;

        main->tree->attr.binary.right = (Tree*)malloc(sizeof(Tree));
        if (main->tree->attr.binary.right == NULL){
            return INTERNAL_ERROR;
        }
        main->tree->attr.binary.right = right->tree;

        //pushnem na Stack koren
        Stack_Push_Element(Stack, main);

        //uvolnujem Stack Elementy
        free(right);
        free(left);   
    }

    //Pravidlo | <(E) -> E |
    else if (Stack_first_nonterm(Stack) == LEFTBRACKET){
        // prava zatvorka ')' nieje ulozena na stacku, ale do Stack elementu bracket si ulozim
        // NETERMINAL E
        bracket = stack_pop_nofree(Stack);


        if (bracket->Item != NOTERM){  //pozeram ci mam v Stack Elemente skutocne neterminal
            return SYNTAX_ERROR;
        }
        Stack_pop(Stack); // vyhadzujem zo stacku pravu zatvorku '('
        Stack_pop(Stack); // vyhadzujem aj zarazku '<'

        Stack_Push_Element(Stack, bracket); // na stack nasledne pushnem neterminal 'E'
    }

    //Pravidlo |<#E -> E|
    else if (Stack_first_nonterm(Stack) == SIZEOF){
        child = stack_pop_nofree(Stack); // do stack Elementu child ulozim NETERMINAL 'E'
        if (child->Item != NOTERM){  // kontrolujem ci je skutocne NETERMINAL
            return SYNTAX_ERROR;
        }

        main = stack_pop_nofree(Stack); // do stack Elementu main ulozim unarny operator
        if (main->Item != SIZEOF){ // kontrolujem ci je to skutocne unarny operator
            return SYNTAX_ERROR;
        }

        Stack_pop(Stack); //vyhadzujem zarazku '<'

        //alokujem poduzol unarneho operatora
        main->tree->attr.unary.child = (Tree*)malloc(sizeof(Tree)); //ako hlavny uzol zvolim Element s operatorom
        if (main->tree->attr.unary.child == NULL){
            return INTERNAL_ERROR;
        }
        main->tree->attr.unary.child = child->tree; //do poduzla nahram hodnotu
        
        main->Item = NOTERM; //zmenim nazov na NOTERM

        Stack_Push_Element(Stack, main); //pushnem upraveny uzol na stack

        //uvolnim stack element
        free(child);
    }

    return PROGRAM_OK;
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

int isExpresionright(Tree *exprTree){
    int isOK = expressionSemanticCheck(exprTree);
    if (isOK == SEMANTICAL_COMPABILITY_ERROR){
        return isOK;
    }
    else if (isOK == DIVISION_ZERO_ERROR){
        return isOK;
    }
    else if (isOK == NIL_ERROR){
        return isOK;
    }
    return PROGRAM_OK;
}


int expressionSemanticCheck(Tree *exprTree){
    int left, right, unary;

    // typ Integer
    if (exprTree->Data->type == Integer){
        if (exprTree->Data->data.integer == 0){
            return INT_zero; 
        }
        return INT;
    }

    // typ Number
    else if (exprTree->Data->type == Number){
        if (exprTree->Data->data.number == 0){
            return NR_zero;
        }
        return NR;
    }

    // typ String
    else if (exprTree->Data->type == String){
        if (strcmp(exprTree->Data->data.string, "") == 0){
            return STR_zero;
        }
        return STR;
    }

    else if(strcmp(exprTree->Data->data.string, "nil") == 0){
        return NIL;
    }

    // Plus, Minus, Multiplication (+, -, *) -- standardne binarne operatory
    else if (exprTree->Data->type == Plus || exprTree->Data->type == Minus ||\
             exprTree->Data->type == Multiplication){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);

        if (left == STR || left == STR_zero || right == STR || right == STR_zero){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if((left == INT && right == INT_zero) || \
                (left == INT && right == NR) || \
                (left == INT && right == NR_zero) || \
                (right == INT && left == INT_zero) || \
                (right == INT && left == NR) || \
                (right == INT && left == NR_zero) || \
                (right == INT_zero && left == NR_zero) || \
                (left == INT_zero && right == NR_zero)){
            return left;
        }

        else if (left == SEMANTICAL_COMPABILITY_ERROR || right == SEMANTICAL_COMPABILITY_ERROR){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if (left == DIVISION_ZERO_ERROR || right == DIVISION_ZERO_ERROR){
            return DIVISION_ZERO_ERROR;
        }

        else if(left == NIL || right == NIL){
            return NIL_ERROR;
        }

        else if (left == right){
            return left;
        }

        return SEMANTICAL_COMPABILITY_ERROR;
    }

    // Concatenation (..)
    else if (exprTree->Data->type == Concatenation){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);

        if(left == NIL || right == NIL){
            return NIL_ERROR;
        }

        // moze byt iba string so stringom
        else if ((left == STR && right == STR) || \
            (left == STR && right == STR_zero) || \
            (right == STR && left == STR_zero) || \
            (left == STR_zero && right == STR_zero)){
            return left;
        }

        else if (left == SEMANTICAL_COMPABILITY_ERROR || right == SEMANTICAL_COMPABILITY_ERROR){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if (left == DIVISION_ZERO_ERROR || right == DIVISION_ZERO_ERROR){
            return DIVISION_ZERO_ERROR;
        }

        return SEMANTICAL_COMPABILITY_ERROR;;
    }

    // Sizeof (#)
    else if (exprTree->Data->type == Sizeof){
        unary = expressionSemanticCheck(exprTree->attr.unary.child);
        
        if(unary == NIL){
            return NIL_ERROR;
        }

        else if (unary != STR && unary != STR_zero){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if (unary == STR_zero){
            return INT_zero;
        }

        return INT;
    }

    // Division, Division_integer (/, //)
    else if (exprTree->Data->type == Division){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);

        if (left == STR || left == STR_zero || right == STR || right == STR_zero){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if (right == NR_zero || right == INT_zero || \
            left == DIVISION_ZERO_ERROR || right == DIVISION_ZERO_ERROR){
            return DIVISION_ZERO_ERROR;
        }

        else if (left == SEMANTICAL_COMPABILITY_ERROR || right == SEMANTICAL_COMPABILITY_ERROR){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if(left == NIL || right == NIL){
            return NIL_ERROR;
        }
        
        return left;
    }

    else if(exprTree->Data->type == Division_integer){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);

        if (left == STR || left == STR_zero || right == STR || right == STR_zero){
            return SEMANTICAL_COMPABILITY_ERROR;
        }

        else if (right == INT_zero || left == DIVISION_ZERO_ERROR || right == DIVISION_ZERO_ERROR){
            return DIVISION_ZERO_ERROR;
        }

        else if ((left == INT && right == INT) || (left == INT_zero && right == INT)){
            return INT;
        }

        else if(left == NIL || right == NIL){
            return NIL_ERROR;
        }

        return SEMANTICAL_COMPABILITY_ERROR;
    }

    else if(exprTree->Data->type == Less || exprTree->Data->type == More || \
            exprTree->Data->type == Less_equal || exprTree->Data->type == More_equal){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);

        if(left == NIL || right == NIL){
            return NIL_ERROR;
        }

        else if(left == right){
            return left;
        }

        else if((left == INT && right == INT_zero) || \
                (left == INT && right == NR) || \
                (left == INT && right == NR_zero) || \
                (right == INT && left == INT_zero) || \
                (right == INT && left == NR) || \
                (right == INT && left == NR_zero)){
            return left;
        }

        return SEMANTICAL_COMPABILITY_ERROR;
    }

    else if (exprTree->Data->type == Not_equal || exprTree->Data->type == Is_equal){
        left = expressionSemanticCheck(exprTree->attr.binary.left);
        right = expressionSemanticCheck(exprTree->attr.binary.right);
        
        if (left == right){
            return left;
        }

        else if (((left == STR || left == NR || left == NR_zero || left == INT || left == INT_zero || left == NIL) && right == NIL) || \
                (right == STR || right == NR || right == NR_zero || right == INT || right == INT_zero || right == NIL) && left == NIL){
            return PROGRAM_OK;
        }
        
    }

    return -1;
}