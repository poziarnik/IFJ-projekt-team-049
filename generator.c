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

#include <stdio.h>
#include <string.h>

//TODO	20,204,230,234

/******************** generovanie funkcii ********************/
int interpret(tFunc *function){
    //TODO 
}

void gen_func_begin(tFunc *function){  
        char *func_name = function->start;          
        printf("\n LABEL $%s\
                \n CREATEFRAME\
                \n PUSHFRAME\n", func_name);
}

void gen_func_end(tFunc *function){
        char *func_name = function->start;
        printf("\nLABEL $%s$end\
                \nPOPFRAME\
                \nRETURN\n", func_name);
}
 

void gen_func_call(char *id){
    printf(" CALL $%s \n", id);
}

void gen_func_def_arg(tFunc *function){
    printf(" DEFVAR LF@%ls", function->param->par_num );
}

void gen_func_arg(tFunc *function){
    printf(" MOVE LF@%s", function->param->id);
}

void gen_func_ret(tFunc *function){
    printf(" POPS LF@return%ls \n", function->retval);
}

/******************** generovanie operacii ********************/

void gen_defvar(char *x){
    printf("\n DEFVAR LF@%s", x);
}

void gen_move(char *x){                             //pri funkcii, MOVE LF@ LF@retval
    printf("\n MOVE  LF@%s LF@%s", x ,x);                   
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
            \n DEFVAR       LF@param\
            \n DEFVAR       LF@retval\
            \n FLOAT2INT    LF@retval LF@param\
            \n POPFRAME\
            \n RETURN\n");
}

void gen_i2f(){
    printf("\n LABEL        $tofloat\
            \n PUSHFRAME\
            \n DEFVAR       LF@param\
            \n DEFVAR       LF@retval\
            \n INT2FLOAT    LF@retval LF@param\
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


