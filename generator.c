/**
 *
 * @file generator.c
 * @author Daniel Zalezak
 * @brief
 * @date 
 *
 */

#include "generator.h"
#include "symtable.h"
#include "ilist.h"

#include <stdio.h>
#include <string.h>

/******************** generovanie funkcii ********************/


void gen_func_begin(char *id){
    if(strcmp(id, "main") == 0){
        printf("\n LABEL $$main\n\
                CREATEFRAME\n\
                PUSHFRAME\n");
    }
    else{
        printf("\n LABEL $%s\
        \n PUSHFRAME\n", id);
    }
}

void gen_func_end(char *id){
    if (strcmp(id, "main") == 0)
    {
        printf(" CLEARS\n\
                RETURN $END OF MAIN\n");
    }
    else{
        printf(" LABEL $ end\n\
                POPFRAME\n\
                RETURN\n");
    }
}

void gen_func_call(char *id){
    printf(" CALL $%s \n", id);
}

void gen_func_def_arg(/*TODO*/){
    printf(" DEFVAR TF@");
}

void gen_func_arg(/*TODO*/){
    printf(" MOVE TF@");
}

void gen_func_ret(int ret){
    printf(" POPS LF@return%d \n", ret);
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

void gen_builtin_func(char *nieco){
    switch(*nieco){
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

        case tofloat:
            gen_i2f();
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
            \n DEFVAR       LF@param1\
            \n DEFVAR       LF@retval0\
            \n FLOAT2INT    LF@retval0 LF@param1\
            \n POPFRAME\
            \n RETURN\n");
}

void gen_i2f(){
    printf("\n LABEL        $tofloat\
            \n PUSHFRAME\
            \n DEFVAR       LF@param1\
            \n DEFVAR       LF@retval0\
            \n INT2FLOAT    LF@retval0 LF@param1\
            \n POPFRAME\
            \n RETURN\n");
}



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

int main(){                     //test
    
    gen_i2f();
    gen_read_i();
    gen_chr();
    gen_f2i();
    gen_read_n();
    gen_read_s();
}
