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


int interpret(root *root){
    printf(".IFJcode21\n");
    if(root->statements != NULL){
        for(int i = 0; i < *root->nbStatements; i++){
            if(root->statements[i]->type == ASTfunction){
                gen_func_begin(root);
                if((*(*root).statements)->TStatement.function->parameters != NULL){
                    for(int a = 0; a < (*(*root->statements)->TStatement.function->nbParameters); a++){
                        gen_func_def_arg(a);
                        gen_func_move_arg(root,a);
                    }
                }
                if((*(*root).statements)->TStatement.function->statements != NULL){
                    //TODO
                }
                for(int a = 0; a < (*(*root->statements)->TStatement.function->nbReturntypes); a++){
                    gen_func_ret(root, a); 
                }
                gen_func_end(root);
            }
            else if(root->statements[i]->type == ASTcondition){
                //TODO
            }
            else if(root->statements[i]->type == ASTcycle){
                //TODO
            }
            // priradenie cisla / stringu DONE - operacie nie 
            else if(root->statements[i]->type == ASTassigne){
                for(int a = 0; a < (*(*root->statements)->TStatement.assignment->nbID); a++ ){
                    if((*(*root->statements)->TStatement.assignment->expressions)->Data->type == Integer){
                        gen_move_int(root, a);
                    }
                    if((*(*root->statements)->TStatement.assignment->expressions)->Data->type == Number){
                        gen_move_number(root, a);
                    }
                    if((*(*root->statements)->TStatement.assignment->expressions)->Data->type == String){
                        gen_move_string(root, a);
                    }
                }

            }
            else if(root->statements[i]->type == ASTdefine){
                gen_defvar(root);
                if((*root->statements)->TStatement.definiton->expression->Data != NULL){
                    //maybe zavolat assign
                }
            }
            // maybe DONE
            else if(root->statements[i]->type == ASTfunctionCall){
                if(isInbuildFun((*root->statements)->TStatement.functioncall->functionName->data.string) == 1){
                    gen_builtin_func(root);
                    if((*root->statements)->TStatement.functioncall->nbID != 0){
                        gen_move_in_func_call(root);
                    }
                }
                else{
                    gen_func_call(root);
                    if((*root->statements)->TStatement.functioncall->nbID != 0){
                        gen_move_in_func_call(root);
                    }
                }
            }
        }
    }
    
}

/******************** generovanie funkcii ********************/

void gen_func_begin(root *root){  
        char *func_name = (*(*root).statements)->TStatement.function->id->data.string;          
        printf("\n LABEL $%s\
                \n CREATEFRAME\
                \n PUSHFRAME\n", func_name);
}

void gen_func_end(root *root){
        char *func_name = (*(*root).statements)->TStatement.function->id->data.string;
        printf("\nLABEL $%s$end\
                \nPOPFRAME\
                \nRETURN\n", func_name);
}
 

void gen_func_call(root *root){
    printf(" CALL $%d \n", (*(*root->statements)->TStatement.functioncall->functionName->data.string));
}

void gen_func_def_arg(int i){
    printf(" DEFVAR LF@%d", i);
}

void gen_func_move_arg(root *root, int i){
    printf(" MOVE LF@%s", (*(*root).statements)->TStatement.function->parameters[i]->data.string);
}

void gen_func_ret(root *root, int i){
    printf(" POPS LF@return%s \n", (*(*root).statements)->TStatement.function->returnTypes[i]->data.string);
}

/******************** generovanie instrukcii ********************/

void gen_defvar(root *root){
    printf("\n DEFVAR LF@%s", (*(*root).statements)->TStatement.definiton->id->data.string);
}

void gen_move_int(root *root, int a){ 
    printf(" \n MOVE LF@%d LF@%d", *(*root->statements)->TStatement.assignment->IDs[a]->data.string, (*root->statements)->TStatement.assignment->expressions[a]->Data->data.integer );
}

void gen_move_string(root *root, int a){ 
    printf(" \n MOVE LF@%d LF@%s", *(*root->statements)->TStatement.assignment->IDs[a]->data.string, (*root->statements)->TStatement.assignment->expressions[a]->Data->data.string );
}

void gen_move_number(root *root, int a){ 
    printf(" \n MOVE LF@%d LF@%f", *(*root->statements)->TStatement.assignment->IDs[a]->data.string, (*root->statements)->TStatement.assignment->expressions[a]->Data->data.number );
}

void gen_move_in_func_call(root *root){                             
    printf("\n MOVE  LF@%s TF@retval" , (*(*root->statements)->TStatement.functioncall->IDs)->data.string);                   
}


void gen_add(char *x){
    printf("\n ADD      LF@retval LF@%s LF@%s" ,x, x);
}

void gen_sub(char *x){
    printf("\n SUB      LF@retval LF@%s LF@%s", x, x);
}

void gen_mul(char *x){
    printf("\n MUL      LF@retval LF@%s LF@%s" ,x, x);
}

void gen_div(char *x){
    printf("\n DIV      LF@retval LF@%s LF@%s", x, x);
}

void gen_idiv(char *x){
    printf("\n IDIV     LF@retval LF@%s LF@%s", x, x);
}

void gen_LT(char *x){
    printf("\n LT       LF@retval LF@%s LF@%s", x, x);
}

void gen_GT(char *x){
    printf("\n GT       LF@retval LF@%s LF@%s", x, x);
}

void gen_EQ(char *x){
    printf("\n EQ       LF@result LF@%s LF@%s", x, x);
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

void gen_builtin_func(root *root){
    switch(*(*root->statements)->TStatement.functioncall->functionName->data.string){
        case readi:
            
            gen_read_i();
            break;

        case reads:
            gen_read_s();
            break;

        case readn:
            gen_read_n();
            break;

        case write:
            gen_write();
            break;

        case tointeger:
            gen_f2i();
            break;

        case substr:
            gen_substr();
            break;

        case ord:
            gen_ord();
            break;

        case chr:
            gen_chr();
            break;

        default:
            break;
    }
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
            \n RETURN\n");   
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
            \n RETURN\n");
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
            \n RETURN\n");
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
            \n RETURN\n");
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
            \n RETURN\n");
}

/*int main(){                     //test
    
    gen_i2f();
    gen_read_i();
    gen_chr();
    gen_f2i();
    gen_read_n();
    gen_read_s();

    char *x = "ahoj";

    gen_defvar(x);

    gen_move(x);

    gen_add(x);

    gen_sub(x);

    gen_mul(x);

    gen_div(x);

    gen_idiv(x);

    gen_LT(x);

    gen_GT(x);
        
    gen_EQ(x);
}*/


