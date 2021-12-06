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
//definica
//pri bin a un operaciach pridat nejaky enum



bool code = true;

int interpret(root *Root){
    if(code == true){
        printf("\n.IFJcode21\n");
        code = false;
    }
    if(Root != NULL){
        if(*Root->statements != NULL && Root->nbStatements != NULL){
            for(int i = 0; i < *Root->nbStatements; i++){
                ///////////////////////////////////////      FUNCTION      /////////////////////////////////////////////////////
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
                /////////////////////////////////////        IF          /////////////////////////////////////////////////////////////////
                else if(Root->statements[i]->type == ASTcondition){
                    //TODO
                }
                ////////////////////////////////////         WHILE       ////////////////////////////////////////////////////////////////
                else if(Root->statements[i]->type == ASTcycle){
                    //TODO
                }
                ////////////////////////////////////        ASSIGNNE     ///////////////////////////////////////////////////////////////
                // priradenie cisla / stringu / jednoduche bin. op DONE - unanrne / zlozene operacie  nie 
                else if(Root->statements[i]->type == ASTassigne){
                    if(*Root->statements[i]->TStatement.assignment->nbID == *Root->statements[i]->TStatement.assignment->nbexpressions){
                        for(int a = 0; a < *Root->statements[i]->TStatement.assignment->nbID; a++ ){ 
                            if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Integer){    
                                gen_move_int(Root,i, a);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Number){
                                gen_move_number(Root,i, a);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == String){
                                gen_move_string(Root,i, a);
                            }

                            ////////////////////////////////////////////  BINARNY STROM /////////////////////////////////////////////////////////
                           /* char INT1[100] = "int@";
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
                                sprintf(num1,"%f",b);
                                first = strcat(float1, num1);  
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->type == String){ 
                                char *b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.string;                                    
                                first = strcat(float1, b);  
                            }
                            
                            if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->type == Integer){
                                int b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->data.integer;
                                char num1[100];
                                sprintf(num1,"%d",b);
                                sec = strcat(INT2, num1);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.right->Data->type == Number){                                    
                                double b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.number;
                                char num1[100];
                                sprintf(num1,"%f",b);
                                sec = strcat(float2, num1);  
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->type == String){
                                char *b = Root->statements[i]->TStatement.assignment->expressions[a]->attr.binary.left->Data->data.string;
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
                            }*/
                        }
                    }   
                }
                //////////////////////////////////////////////      DEFINE      ////////////////////////////////////////////////////////////////////
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
                ///////////////////////////////////////////////     FUNCTION CALL       ///////////////////////////////////////////////////////////
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

void gen_move_int(root *root,int i, int a){ 
    printf(" \n MOVE LF@%s int@%d", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.integer );
    
}

void gen_move_string(root *root, int i, int a){ 
    printf(" \n MOVE LF@%s string@%s", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.string );
}

void gen_move_number(root *root,int i,  int a){ 
    printf(" \n MOVE LF@%s float@%f", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.number);
}

void gen_move_int_indef(root *root,int i){ 
    printf(" \n MOVE LF@%s int@%d", root->statements[i]->TStatement.definiton->id->data.string, root->statements[i]->TStatement.definiton->ExFc.expression->Data->data.integer );
    
}

void gen_move_string_indef(root *root, int i){ 
    printf(" \n MOVE LF@%s string@%s", root->statements[i]->TStatement.definiton->id->data.string, root->statements[i]->TStatement.definiton->ExFc.expression->Data->data.string );
}

void gen_move_number_indef(root *root,int i){ 
    printf(" \n MOVE LF@%s float@%f", root->statements[i]->TStatement.definiton->id->data.string, root->statements[i]->TStatement.definiton->ExFc.expression->Data->data.number);
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

void gen_LT(char *x){
    printf("\n LT   LF@retval LF@%s LF@%s", x, x);
}

void gen_GT(char *x){
    printf("\n GT   LF@retval LF@%s LF@%s", x, x);
}

void gen_EQ(char *x){
    printf("\n EQ   LF@result LF@%s LF@%s", x, x);
}

/******************** generovanie cyklov ********************/

void gen_if(){
//TODO
}

void gen_else(){
//TODO
}

void gen_while(){
//TODO
}

void gen_then(){
//TODO
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


