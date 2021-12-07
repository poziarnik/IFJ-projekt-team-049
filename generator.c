/**
 *
 * @file generator.c
 * @author Daniel Zalezak
 * @brief
 * @date 
 *
 */

#include "generator.h"
#include "ilist.h"
#include "AST.h"
#include "symtable.h"

#include <stdio.h>
#include <string.h>


//inbuild na zaciatku
// nil v cykle
//velkost pola



bool code = true;
int while_cycle_counter = 1;
int if_cycle_counter = 1;

int interpret(root *Root){
    if(code == true){
        printf("\n.IFJcode21\n");
        code = false;
    }
    if(Root != NULL){
        if(*Root->statements != NULL && Root->nbStatements != NULL){
            for(int i = 0; i < *Root->nbStatements; i++){
///////////////////////////////////////////////////////////      FUNCTION      /////////////////////////////////////////////////////
                if(Root->statements[i]->type == ASTfunction){   
                    gen_func_begin(Root, i);
                    if(Root->statements[i]->TStatement.function->nbParameters != NULL){
                        for(int a = 1; a < *Root->statements[i]->TStatement.function->nbParameters + 1 ; a++){  
                            gen_func_def_arg(a);
                        }
                        for(int a = 0; a < *Root->statements[i]->TStatement.function->nbParameters ; a++){  
                            gen_func_move_arg(Root,i,a);
                        }
                    } 
                    /////////////////////////////////   FUNCTION   STATEMENTS      //////////////////////////////////////////////////////
                    if(*Root->statements[i]->TStatement.function->statements != NULL){   
                        Tstate *funcRoot = ASTcreateLeaf(ASTglobal);
                        for(int b = 0; b < *Root->statements[i]->TStatement.function->nbStatements; b++){
                            funcRoot->TStatement.root->statements[b] = Root->statements[i]->TStatement.function->statements[b];
                        }
                        funcRoot->TStatement.root->nbStatements = Root->statements[i]->TStatement.function->nbStatements;
                        interpret(funcRoot->TStatement.root);
                    }
                    for(int a = 0; a < *Root->statements[i]->TStatement.function->nbReturntypes; a++){
                        gen_func_ret(Root,i, a); 
                    }
                    gen_func_end(Root, i);
                }
////////////////////////////////////////////////////////        IF          /////////////////////////////////////////////////////////////////
                else if(Root->statements[i]->type == ASTcondition){
                    char *left1;
                    char *right2;
                    if(Root->statements[i]->TStatement.if_loop->expression->Data->type == More || Less || More_equal || Less_equal || Is_equal || Not_equal ){
                        char INT1[100] = "int@";
                        char float1[100] = "float@";
                        char string1[100] = "string@";
                        char var1[100] = "LF@";
                        if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Integer){                                
                            int b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->data.integer;
                            char num1[100];
                            sprintf(num1,"%d",b);
                            left1 = strcat(INT1, num1);
                        }
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Number){   
                            double b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->data.number;
                            char num1[100];
                            sprintf(num1,"%a",b);
                            left1 = strcat(float1, num1);
                        }
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == String){                
                            char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->data.string;
                            char num1[100];
                            sprintf(num1,"%s",b);
                            left1 = strcat(string1, num1);
                        }
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Identifier){                        
                            char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->data.string;
                            char num1[100];
                            sprintf(num1,"%s",b);
                            left1 = strcat(var1, num1);
                        }
                            
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Minus || Plus || Multiplication || Division || Division_integer ){
                            char INT1[100] = "int@";
                            char INT2[100] = "int@";
                            char float1[100] = "float@";
                            char float2[100] = "float@";
                            char var1[100] = "LF@";
                            char var2[100] = "LF@";
                            char *first;
                            char *sec;
                            if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.left->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.left->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                first = strcat(INT1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.left->Data->type == Number){
                                double b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.left->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                first = strcat(float1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.left->Data->type == Identifier){ 
                                char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.left->Data->data.string;                                    
                                first = strcat(var1, b);  
                            }
                                    
                            if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.right->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.right->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                sec = strcat(INT2, num1);
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.right->Data->type == Number){                                    
                                double b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.right->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                sec = strcat(float2, num1);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.right->Data->type == Identifier){
                                char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->attr.binary.right->Data->data.string;
                                sec = strcat(var2, b);  
                            } 

                            ////////////////////////////////////   BINARNE OPERACIE   ///////////////////////////////////////////////////////////////
                            if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Minus){
                                gen_sub(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Plus){
                                gen_add(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);   
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Multiplication){
                                gen_mul(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Division){
                                gen_div(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.left->Data->type == Division_integer){
                                gen_idiv(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);
                            }
                            left1 = "LF@left_side";
                        }
                        
                        if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Integer){
                            char INT5[100] = "int@";
                            int c = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->data.integer;
                            char num5[100];
                            sprintf(num5,"%d",c);                               
                            right2 = strcat(INT5, num5); 
                        }
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Number){
                            double b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->data.number;
                            char float5[100] = "float@";
                            char num1[100];
                            sprintf(num1,"%a",b);
                            right2 = strcat(float5, num1);
                        }
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == String){
                            char string5[100] = "string@";
                            char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->data.string;
                            char num1[100];
                            sprintf(num1,"%s",b);
                            right2 = strcat(string5, num1);
                        }
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Identifier){
                            char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->data.string;
                            char var5[100] = "LF@";
                            char num1[100];
                            sprintf(num1,"%s",b);
                            right2 = strcat(var5, num1);
                        }
                        
                        else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Minus || Plus || Multiplication || Division || Division_integer ){
                            char INT1[100] = "int@";
                            char INT2[100] = "int@";
                            char float1[100] = "float@";
                            char float2[100] = "float@";
                            char var1[100] = "LF@";
                            char var2[100] = "LF@";
                            char *first;
                            char *sec;
                            if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.left->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.left->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                first = strcat(INT1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.left->Data->type == Number){
                                double b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.left->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                first = strcat(float1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.left->Data->type == Identifier){ 
                                char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.left->Data->data.string;                                    
                                first = strcat(var1, b);  
                            }
                                    
                            if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.right->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.right->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                sec = strcat(INT2, num1);
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.right->Data->type == Number){                                    
                                double b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.right->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                sec = strcat(float2, num1);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.right->Data->type == Identifier){
                                char *b = Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->attr.binary.right->Data->data.string;
                                sec = strcat(var2, b);  
                            } 

                            ////////////////////////////////////   BINARNE OPERACIE   ///////////////////////////////////////////////////////////////
                            if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Minus){
                                gen_sub(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Plus){
                                gen_add(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);   
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Multiplication){
                                gen_mul(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Division){
                                gen_div(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.if_loop->expression->attr.binary.right->Data->type == Division_integer){
                                gen_idiv(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);
                            }
                            right2 = "LF@right_side";
                        }
                
                        
                    }
                   
                    
                    if(Root->statements[i]->TStatement.if_loop->expression->Data->type == More){
                        gen_GT(left1, right2);
                        if(Root->statements[i]->TStatement.if_loop->hasElse == false){
                            gen_JUMPIFEQ("then","LF@GTretval", "bool@true");
                        }
                        else gen_JUMPIFNEQ("else","LF@GTretval", "bool@true");
                        
                    }
                    else if(Root->statements[i]->TStatement.if_loop->expression->Data->type == Less){
                        gen_LT(left1, right2);
                        if(Root->statements[i]->TStatement.if_loop->hasElse == false){
                            gen_JUMPIFEQ("then","LF@LTretval", "bool@true");
                        }
                        else gen_JUMPIFNEQ("else","LF@LTretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.if_loop->expression->Data->type == More_equal){
                        gen_GT(left1, right2);
                        gen_EQ(left1, right2);
                        gen_OR("LF@GTretval", "LF@EQretval");
                        if(Root->statements[i]->TStatement.if_loop->hasElse == false){
                            gen_JUMPIFEQ("then","LF@ORretval", "bool@true");
                        }
                        else gen_JUMPIFNEQ("else","LF@ORretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.if_loop->expression->Data->type == Less_equal){
                        gen_LT(left1, right2);
                        gen_EQ(left1, right2);
                        gen_OR("LF@LTretval", "LF@EQretval");
                        if(Root->statements[i]->TStatement.if_loop->hasElse == false){
                            gen_JUMPIFEQ("then","LF@ORretval", "bool@true");
                        }
                        else gen_JUMPIFNEQ("else","LF@ORretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.if_loop->expression->Data->type == Is_equal){
                        gen_EQ(left1, right2);
                        if(Root->statements[i]->TStatement.if_loop->hasElse == false){
                            gen_JUMPIFEQ("then","LF@EQretval", "bool@true");
                        }
                        else gen_JUMPIFNEQ("else","LF@EQretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.if_loop->expression->Data->type == Not_equal){
                        gen_EQ(left1, right2);
                        if(Root->statements[i]->TStatement.if_loop->hasElse == false){
                            gen_JUMPIFNEQ("then","LF@EQretval", "bool@true");
                        }
                        else gen_JUMPIFEQ("else","LF@EQretval", "bool@true");
                    }
                    gen_then(if_cycle_counter);
                    if(*Root->statements[i]->TStatement.if_loop->if_statements != NULL){   
                        if_cycle_counter ++;
                        Tstate *thenRoot = ASTcreateLeaf(ASTglobal);
                        for(int b = 0; b < *Root->statements[i]->TStatement.if_loop->nbIfStatements; b++){
                            thenRoot->TStatement.root->statements[b] = Root->statements[i]->TStatement.if_loop->if_statements[b];
                        }
                        thenRoot->TStatement.root->nbStatements = Root->statements[i]->TStatement.if_loop->nbIfStatements;
                        interpret(thenRoot->TStatement.root);
                        if_cycle_counter --;
                    }
                    gen_jump_end(if_cycle_counter);
                    if(*Root->statements[i]->TStatement.if_loop->hasElse == true){
                        gen_else(if_cycle_counter);
                        if(*Root->statements[i]->TStatement.if_loop->else_statements != NULL){   
                            if_cycle_counter ++;
                            Tstate *elseRoot = ASTcreateLeaf(ASTglobal);
                            for(int b = 0; b < *Root->statements[i]->TStatement.if_loop->nbElseStatements; b++){
                                elseRoot->TStatement.root->statements[b] = Root->statements[i]->TStatement.if_loop->else_statements[b];
                            }
                            elseRoot->TStatement.root->nbStatements = Root->statements[i]->TStatement.if_loop->nbElseStatements;
                            interpret(elseRoot->TStatement.root);
                            if_cycle_counter --;
                        }
                        gen_jump_end(if_cycle_counter);
                    }
                    gen_end(if_cycle_counter);
                }
//////////////////////////////////////////////////////         WHILE       ////////////////////////////////////////////////////////////////
                else if(Root->statements[i]->type == ASTcycle){
                    gen_while(while_cycle_counter);
                    char *left1;
                    char *right2;
                    if(Root->statements[i]->TStatement.while_loop->expression->Data->type == More || Less || More_equal || Less_equal || Is_equal || Not_equal ){
                        char INT1[100] = "int@";
                        char float1[100] = "float@";
                        char string1[100] = "string@";
                        char var1[100] = "LF@";
                        if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Integer){                                
                            int b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->data.integer;
                            char num1[100];
                            sprintf(num1,"%d",b);
                            left1 = strcat(INT1, num1);
                        }
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Number){   
                            double b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->data.number;
                            char num1[100];
                            sprintf(num1,"%a",b);
                            left1 = strcat(float1, num1);
                        }
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == String){                
                            char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->data.string;
                            char num1[100];
                            sprintf(num1,"%s",b);
                            left1 = strcat(string1, num1);
                        }
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Identifier){                        
                            char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->data.string;
                            char num1[100];
                            sprintf(num1,"%s",b);
                            left1 = strcat(var1, num1);
                        }
                            
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Minus || Plus || Multiplication || Division || Division_integer ){
                            char INT1[100] = "int@";
                            char INT2[100] = "int@";
                            char float1[100] = "float@";
                            char float2[100] = "float@";
                            char var1[100] = "LF@";
                            char var2[100] = "LF@";
                            char *first;
                            char *sec;
                            if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.left->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.left->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                first = strcat(INT1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.left->Data->type == Number){
                                double b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.left->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                first = strcat(float1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.left->Data->type == Identifier){ 
                                char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.left->Data->data.string;                                    
                                first = strcat(var1, b);  
                            }
                                    
                            if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.right->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.right->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                sec = strcat(INT2, num1);
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.right->Data->type == Number){                                    
                                double b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.right->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                sec = strcat(float2, num1);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.right->Data->type == Identifier){
                                char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->attr.binary.right->Data->data.string;
                                sec = strcat(var2, b);  
                            } 

                            ////////////////////////////////////   BINARNE OPERACIE   ///////////////////////////////////////////////////////////////
                            if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Minus){
                                gen_sub(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Plus){
                                gen_add(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);   
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Multiplication){
                                gen_mul(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Division){
                                gen_div(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.left->Data->type == Division_integer){
                                gen_idiv(first, sec);
                                char *var = "LF@left_side";
                                gen_move_in_func_call(var);
                            }
                            left1 = "LF@left_side";
                        }
                        
                        if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Integer){
                            char INT5[100] = "int@";
                            int c = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->data.integer;
                            char num5[100];
                            sprintf(num5,"%d",c);                               
                            right2 = strcat(INT5, num5); 
                        }
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Number){
                            double b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->data.number;
                            char float5[100] = "float@";
                            char num1[100];
                            sprintf(num1,"%a",b);
                            right2 = strcat(float5, num1);
                        }
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == String){
                            char string5[100] = "string@";
                            char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->data.string;
                            char num1[100];
                            sprintf(num1,"%s",b);
                            right2 = strcat(string5, num1);
                        }
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Identifier){
                            char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->data.string;
                            char var5[100] = "LF@";
                            char num1[100];
                            sprintf(num1,"%s",b);
                            right2 = strcat(var5, num1);
                        }
                        
                        else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Minus || Plus || Multiplication || Division || Division_integer ){
                            char INT1[100] = "int@";
                            char INT2[100] = "int@";
                            char float1[100] = "float@";
                            char float2[100] = "float@";
                            char var1[100] = "LF@";
                            char var2[100] = "LF@";
                            char *first;
                            char *sec;
                            if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.left->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.left->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                first = strcat(INT1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.left->Data->type == Number){
                                double b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.left->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                first = strcat(float1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.left->Data->type == Identifier){ 
                                char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.left->Data->data.string;                                    
                                first = strcat(var1, b);  
                            }
                                    
                            if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.right->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.right->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                sec = strcat(INT2, num1);
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.right->Data->type == Number){                                    
                                double b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.right->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%a",b);
                                sec = strcat(float2, num1);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.right->Data->type == Identifier){
                                char *b = Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->attr.binary.right->Data->data.string;
                                sec = strcat(var2, b);  
                            } 

                            ////////////////////////////////////   BINARNE OPERACIE   ///////////////////////////////////////////////////////////////
                            if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Minus){
                                gen_sub(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Plus){
                                gen_add(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);   
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Multiplication){
                                gen_mul(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Division){
                                gen_div(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);  
                            }
                            else if(Root->statements[i]->TStatement.while_loop->expression->attr.binary.right->Data->type == Division_integer){
                                gen_idiv(first, sec);
                                char *var = "LF@right_side";
                                gen_move_in_func_call(var);
                            }
                            right2 = "LF@right_side";
                        }
                
                        
                    }
                   
                    
                    if(Root->statements[i]->TStatement.while_loop->expression->Data->type == More){
                        gen_GT(left1, right2);
                        gen_JUMPIFNEQ("end","LF@GTretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.while_loop->expression->Data->type == Less){
                        gen_LT(left1, right2);
                        gen_JUMPIFNEQ("end","LF@LTretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.while_loop->expression->Data->type == More_equal){
                        gen_GT(left1, right2);
                        gen_EQ(left1, right2);
                        gen_OR("LF@GTretval", "LF@EQretval");
                        gen_JUMPIFNEQ("end","LF@ORretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.while_loop->expression->Data->type == Less_equal){
                        gen_LT(left1, right2);
                        gen_EQ(left1, right2);
                        gen_OR("LF@LTretval", "LF@EQretval");
                        gen_JUMPIFNEQ("end","LF@ORretval", "bool@true");
                    }
                    else if(Root->statements[i]->TStatement.while_loop->expression->Data->type == Is_equal){
                        gen_JUMPIFNEQ("end",left1, right2);
                    }
                    else if(Root->statements[i]->TStatement.while_loop->expression->Data->type == Not_equal){
                        gen_JUMPIFEQ("end",left1, right2);
                    }
                    
                    if(*Root->statements[i]->TStatement.while_loop->do_statement != NULL){   
                        while_cycle_counter ++;
                        Tstate *whileRoot = ASTcreateLeaf(ASTglobal);
                        for(int b = 0; b < *Root->statements[i]->TStatement.while_loop->nbStatements; b++){
                            whileRoot->TStatement.root->statements[b] = Root->statements[i]->TStatement.while_loop->do_statement[b];
                        }
                        whileRoot->TStatement.root->nbStatements = Root->statements[i]->TStatement.while_loop->nbStatements;
                        interpret(whileRoot->TStatement.root);
                        while_cycle_counter --;
                    }
                    gen_while_end(while_cycle_counter);
                    
                }
//////////////////////////////////////////////////        ASSIGNNE     ///////////////////////////////////////////////////////////////
                // priradenie cisla / stringu / jednoduche bin. unanrne  op DONE -  zlozene operacie  nie 
                else if(Root->statements[i]->type == ASTassigne){
                    if(*Root->statements[i]->TStatement.assignment->nbID == *Root->statements[i]->TStatement.assignment->nbexpressions){
                        for(int a = 0; a < *Root->statements[i]->TStatement.assignment->nbID; a++ ){ 
                            if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Integer){  
                                char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                int num = Root->statements[i]->TStatement.assignment->expressions[a]->Data->data.integer;
                                gen_move_int(var, num);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Number){
                                gen_move_number(Root,i, a);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == String){
                                gen_move_string(Root,i, a);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Identifier){
                                gen_move_string(Root,i, a);
                            }
                            ////////////////////////////////////////// UNARNE OPERACIE ////////////////////////////////////////////////////////////////
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Sizeof){
                                    char *string = Root->statements[i]->TStatement.assignment->expressions[a]->attr.unary.child->Data->data.string;
                                    gen_strlen(string);
                                    char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                    gen_move_in_func_call(var);                            
                                }
                            
                            ////////////////////////////////////////////  BINARNY STROM /////////////////////////////////////////////////////////
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Minus || Plus || Multiplication || Division || Division_integer ){
                                char INT1[100] = "int@";
                                char INT2[100] = "int@";
                                char float1[100] = "float@";
                                char float2[100] = "float@";
                                char var1[100] = "LF@";
                                char var2[100] = "LF@";
                                char *first;
                                char *sec;
                                if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->type == Integer){
                                    int b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.integer;
                                    char num1[100];
                                    sprintf(num1,"%d",b);
                                    first = strcat(INT1, num1);  
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->type == Number){
                                    double b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.number;
                                    char num1[100];
                                    sprintf(num1,"%a",b);
                                    first = strcat(float1, num1);  
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->type == String ){ 
                                    char *b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.string;                                    
                                    first = strcat(var1, b);  
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->type == Identifier ){ 
                                    char *b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.string;                                    
                                    first = strcat(var1, b);  
                                }
                                
                                if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->type == Integer){
                                    int b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->data.integer;
                                    char num1[100];
                                    sprintf(num1,"%d",b);
                                    sec = strcat(INT2, num1);
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->type == Number){                                    
                                    double b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->data.number;
                                    char num1[100];
                                    sprintf(num1,"%a",b);
                                    sec = strcat(float2, num1);  
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->type == String ){
                                    char *b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->data.string;
                                    sec = strcat(var2, b);  
                                } 

                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->type == Identifier ){
                                    char *b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->data.string;
                                    sec = strcat(var2, b);  
                                } 

                                ////////////////////////////////////   BINARNE OPERACIE   ///////////////////////////////////////////////////////////////
                                if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Minus){
                                    gen_sub(first, sec);
                                    char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                    gen_move_in_func_call(var);
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Plus){
                                    gen_add(first, sec);
                                    char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                    gen_move_in_func_call(var);   
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Multiplication){
                                    gen_mul(first, sec);
                                    char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                    gen_move_in_func_call(var);  
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Division){
                                    gen_div(first, sec);
                                    char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                    gen_move_in_func_call(var);  
                                }
                                else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Division_integer){
                                    gen_idiv(first, sec);
                                    char *var = Root->statements[i]->TStatement.assignment->IDs[a]->data.string;
                                    gen_move_in_func_call(var);
                                }
                                
                            }
                            
                        }
                    }   
                }
//////////////////////////////////////////////////////////////////      DEFINE      ////////////////////////////////////////////////////////////////////
                else if(Root->statements[i]->type == ASTdefine){
                    gen_defvar(Root, i);
                    if(Root->statements[i]->TStatement.definiton != NULL){
                        if(*Root->statements[i]->TStatement.definiton->state == FCcall){
                            if(isInbuildFun(Root->statements[i]->TStatement.definiton->ExFc.FCcall->TStatement.functioncall->functionName->data.string) == true){
                                Root->statements[i]->TStatement.functioncall->functionName->data.string = Root->statements[i]->TStatement.definiton->ExFc.FCcall->TStatement.functioncall->functionName->data.string;
                                gen_builtin_func(Root,i);
                                char *var = Root->statements[i]->TStatement.definiton->id->data.string;
                                gen_move_in_func_call(var);  
                            }
                            else{
                                gen_func_call(Root, i);                                                                        
                                char *var = Root->statements[i]->TStatement.definiton->id->data.string;
                                gen_move_in_func_call(var);
                            }
                        }
                
                        else if(*Root->statements[i]->TStatement.definiton->state == Expression){
                            if(Root->statements[i]->TStatement.definiton->ExFc.expression->Data->type == Integer){
                                gen_move_int_indef(Root, i);
                            }
                            else if(Root->statements[i]->TStatement.definiton->ExFc.expression->Data->type == String){
                                gen_move_string_indef(Root, i);
                            }
                            else if(Root->statements[i]->TStatement.definiton->ExFc.expression->Data->type == Number){
                                gen_move_number_indef(Root, i);
                            }
                        }
                    }
                    
                }
//////////////////////////////////////////////////////////////     FUNCTION CALL       ///////////////////////////////////////////////////////////
                // maybe DONE 
                else if(Root->statements[i]->type == ASTfunctionCall){
                    if(isInbuildFun(Root->statements[i]->TStatement.functioncall->functionName->data.string) == true){
                        gen_builtin_func(Root,i);
                        if(*Root->statements[i]->TStatement.functioncall->nbID != 0 != 0){
                            for(int a = 0; a < *Root->statements[i]->TStatement.functioncall->nbID; a++){
                                char *var = Root->statements[i]->TStatement.functioncall->IDs[a]->data.string;
                                gen_move_in_func_call(var);
                            }
                        }
                    }
                    else{
                        gen_func_call(Root, i);                                                                        //prepisat
                        if( *Root->statements[i]->TStatement.functioncall->nbID != 0){  
                           for(int a = 0; a < *Root->statements[i]->TStatement.functioncall->nbID; a++){
                                char *var = Root->statements[i]->TStatement.functioncall->IDs[a]->data.string;
                                gen_move_in_func_call(var);
                            }
                        }
                    }
                }
            }
        }
    }
}

/******************** generovanie funkcii ********************/

void gen_func_begin(root *root, int i){  
        char *func_name = root->statements[i]->TStatement.function->id->data.string;       
        printf("\n LABEL $%s\
                \n CREATEFRAME\
                \n PUSHFRAME", func_name);
}

void gen_func_end(root *root, int i){
        char *func_name = root->statements[i]->TStatement.function->id->data.string;
        printf("\n LABEL $%s$end\
                \n POPFRAME\
                \n RETURN", func_name);
}
 

void gen_func_call(root *root, int i){
    printf(" CALL $%s \n", root->statements[i]->TStatement.functioncall->functionName->data.string);
    
}

void gen_func_def_arg(int i){
    printf("\n DEFVAR LF@%d", i);
}

void gen_func_move_arg(root *root, int i, int a){
    printf("\n MOVE LF@%s", root->statements[i]->TStatement.function->parameters[a]->data.string );
    
}

void gen_func_ret(root *root, int i, int a){
    printf("\n POPS LF@return$%s", root->statements[i]->TStatement.function->returnTypes[a]->data.string);
} 

/******************** generovanie instrukcii ********************/

void gen_defvar(root *root, int i){
    printf("\n DEFVAR LF@%s", root->statements[i]->TStatement.definiton->id->data.string);
    
}

void gen_move_int(char *var, int i){ 
    printf(" \n MOVE LF@%s int@%d", var, i );
}

void gen_move_string(root *root, int i, int a){ 
    printf(" \n MOVE LF@%s string@%s", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.string );
}

void gen_move_number(root *root,int i,  int a){ 
    printf(" \n MOVE LF@%s float@%a", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.number);
}

void gen_move_int_indef(root *root,int i){ 
    printf(" \n MOVE LF@%s int@%d", root->statements[i]->TStatement.definiton->id->data.string, root->statements[i]->TStatement.definiton->ExFc.expression->Data->data.integer );
    
}

void gen_move_string_indef(root *root, int i){ 
    printf(" \n MOVE LF@%s string@%s", root->statements[i]->TStatement.definiton->id->data.string, root->statements[i]->TStatement.definiton->ExFc.expression->Data->data.string );
}

void gen_move_number_indef(root *root,int i){ 
    printf(" \n MOVE LF@%s float@%a", root->statements[i]->TStatement.definiton->id->data.string, root->statements[i]->TStatement.definiton->ExFc.expression->Data->data.number);
}

void gen_move_in_func_call(char *var){                             
    printf("\n MOVE  LF@%s TF@retval" , var );   
}


void gen_add(char *first, char *second){
    printf("\n ADD  LF@retval %s %s" ,first, second);
}

void gen_sub(char *first, char *second){
    printf("\n SUB  LF@retval %s %s ", first, second);
}

void gen_mul(char *first, char *second){
    printf("\n MUL  LF@retval %s %s" ,first, second);
}

void gen_div(char *first, char *second){
    printf("\n DIV  LF@retval %s %s", first, second);
}

void gen_idiv(char *first, char *second){
    printf("\n IDIV  LF@retval %s %s", first, second);
}

void gen_strlen(char *string){
    printf("\n STRLEN  LF@retval string@%s", string);  
}


void gen_LT(char *first, char *second){
    printf("\n LT   LF@LTretval %s %s", first, second);
}

void gen_GT(char *first, char *second){
    printf("\n GT   LF@GTretval %s %s", first, second);
}

void gen_EQ(char *first, char *second){
    printf("\n EQ   LF@EQretval %s %s", first, second);
}

void gen_JUMPIFEQ(char *jump ,char *first, char *second){
    printf("\n JUMPIFEQ   %s %s %s",jump, first, second);
}

void gen_JUMPIFNEQ(char *jump ,char *first, char *second){
    printf("\n JUMPIFNEQ   %s %s %s",jump, first, second);
}

void gen_OR(char *first, char *second){
    printf("\n OR   LF@ORretval %s %s", first, second);
}

/******************** generovanie cyklov ********************/

void gen_then(int counter){
    printf("\n LABEL then$%d", counter);
}

void gen_jump_end(int counter){
    printf("\n JUMP end$%d", counter);
}

void gen_else(int counter){
    printf("\n LABEL else$%d", counter );
}

void gen_end(int counter){
    printf("\n LABEL end$%d", counter);
}

void gen_while(int i){
    printf("\n LABEL while$%d", i);
}

void gen_while_end(int i){
    printf("\n JUMP while$%d\
            \n LABEL end$%d", i, i);
}

/******************** generovanie vstavanych funkcii ********************/

void gen_builtin_func(root *root, int i){
    if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "readi") == 0)
            gen_read_i();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "reads") == 0)       
            gen_read_s();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "readn") == 0)
            gen_read_n();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "write") == 0)
            gen_write();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "tointeger") == 0)
            gen_f2i();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "substr") == 0)
            gen_substr();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "ord") == 0)
            gen_ord();
    else if(strcmp(root->statements[i]->TStatement.functioncall->functionName->data.string, "chr") == 0)
            gen_chr();
            
}

int gen_read_i(){
    printf("\n LABEL        $readi\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval0\
            \n DEFVAR       LF@retval1\
            \n MOVE         LF@retval1 int@0\
            \n DEFVAR       LF@typeout\
            \n READ         LF@retval0 int\
            \n TYPE         LF@typeout LF@retval0\
            \n JUMPIFEQ     $readi$istrue LF@typeout string@int\
            \n MOVE         LF@retval0 int@1\
            \n MOVE         LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\
            \n LABEL        $readi$istrue\
            \n POPFRAME\
            \n RETURN");   
}

int gen_read_s(){
    printf("\n LABEL        $reads\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval0\
            \n DEFVAR       LF@retval1\
            \n MOVE         LF@retval1 int@0\
            \n READ         LF@retval0 string\
            \n JUMPIFNEQ    $reads$noerr LF@retval0 nil@nil\
            \n MOVE         LF@retval1 int@1\
            \n LABEL        $reads$noerr\
            \n POPFRAME\
            \n RETURN");
}

int gen_read_n(){
    printf("\n LABEL        $readn\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval0\
            \n DEFVAR       LF@retval1\
            \n MOVE         LF@retval1 int@0\
            \n DEFVAR       LF@typeout\
            \n READ         LF@retval0 float\
            \n TYPE         LF@typeout LF@retval0\
            \n JUMPIFEQ     $readn$istrue LF@typeout string@float\
            \n MOVE         LF@retval0 float@0x1p+0\
            \n MOVE         LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\
            \n LABEL        $readn$istrue\
            \n POPFRAME\
            \n RETURN");
}

void gen_write(){
    printf("\n LABEL $write\
            \n PUSHFRAME\
            \n");
            //TODO
}

void gen_f2i(){
    printf("\n LABEL        $tointeger\
            \n PUSHFRAME\
            \n DEFVAR       LF@param\
            \n DEFVAR       LF@retval\
            \n FLOAT2INT    LF@retval LF@param\
            \n POPFRAME\
            \n RETURN");
}

/*void gen_i2f(){
    printf("\n LABEL        $tofloat\
            \n PUSHFRAME\
            \n DEFVAR       LF@param\
            \n DEFVAR       LF@retval\
            \n INT2FLOAT    LF@retval LF@param\
            \n POPFRAME\
            \n RETURN\n");
}*/



void gen_substr(){
//TODO
}

void gen_ord(){
//TODO
}

void gen_chr(){
    printf("\n LABEL        $chr\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval1\
            \n DEFVAR       LF@retval0\
            \n GT           LF@retval1 LF@param0 int@255\
            \n JUMPIFEQ     $chr$error LF@retval1 bool@true\
            \n LT           LF@retval1 LF@param0 int@0\
            \n JUMPIFEQ     $chr$error LF@retval1 bool@true\
            \n INT2CHAR     LF@retval0 LF@param0\
            \n MOVE         LF@retval1 int@0\
            \n POPFRAME\
            \n RETURN\
            \n LABEL        $chr$error\
            \n MOVE         LF@retval0 string@\
            \n MOVE         LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN");
}


