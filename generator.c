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
        printf("\n LABEL $main\n\
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
                JUMP $EOF\n");
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
        case I_READI:
            gen_read_i();
            break;

        case I_READS:
            gen_read_s();
            break;

        case I_READN:
            gen_read_n();
            break;

        case I_WRITE:
            gen_write();
            break;

        case I_F2I:
            gen_f2i();
            break;

        case I_I2F:
            gen_i2f();
            break;

        default:
            break;
    }
}

int gen_read_i(){
    printf("\n LABEL $inputi\
            \n PUSHFRAME\
            \n DEFVAR LF@retval0\
            \n DEFVAR LF@retval1\
            \n MOVE LF@retval1 int@0\
            \n DEFVAR LF@typeout\
            \n READ LF@retval0 int\
            \n TYPE LF@typeout LF@retval0\
            \n JUMPIFEQ $inputi$istrue LF@typeout string@int\
            \n MOVE LF@retval0 int@1\
            \n MOVE LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\
            \n LABEL $inputi$istrue\
            \n POPFRAME\
            \n RETURN\n");   
}

int gen_read_s(){
    printf("\n LABEL $inputs\
            \n PUSHFRAME\
            \n DEFVAR LF@retval0\
            \n DEFVAR LF@retval1\
            \n MOVE LF@retval1 int@0\
            \n READ LF@retval0 string\
            \n JUMPIFNEQ $inputs$noerr LF@retval0 nil@nil\
            \n MOVE LF@retval1 int@1\
            \n LABEL $inputs$noerr\
            \n POPFRAME\
            \n RETURN\n");
}

int gen_read_n(){
    printf("\n LABEL $inputf\
            \n PUSHFRAME\
            \n DEFVAR LF@retval0\
            \n DEFVAR LF@retval1\
            \n MOVE LF@retval1 int@0\
            \n DEFVAR LF@typeout\
            \n READ LF@retval0 float\
            \n TYPE LF@typeout LF@retval0\
            \n JUMPIFEQ $inputf$istrue LF@typeout string@float\
            \n MOVE LF@retval0 float@0x1p+0\
            \n MOVE LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\
            \n LABEL $inputf$istrue\
            \n POPFRAME\
            \n RETURN\n");
}

void gen_write(){
    printf("\n LABEL $write\
            \n PUSHFRAME\
            \n");
}

void gen_f2i(){
    printf("\n LABEL $float2int\
            \n PUSHFRAME\
            \n DEFVAR LF@param1\
            \n DEFVAR LF@retval0\
            \n FLOAT2INT LF@retval0 LF@param1\
            \n POPFRAME\
            \n RETURN\n");
}

void gen_i2f(){
    printf("\n LABEL $int2float\
            \n PUSHFRAME\
            \n DEFVAR LF@param1\
            \n DEFVAR LF@retval0\
            \n INT2FLOAT LF@retval0 LF@param1\
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
//TODO
}

int main(){                     //test
    char *e = "ahoj";
    printf("\nLABEL $%s"\
        "\nPUSHFRAME\n", e);
    gen_i2f();
}
