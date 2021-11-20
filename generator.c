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

void gen_builtin_func(){
//TODO
}

int gen_read_i(){
//TODO
}

int gen_read_s(){
//TODO
}

int gen_read_n(){
//TODO
}

void gen_write(){
//TODO
}

void gen_f2i(){
//TODO
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

int main(){
    char *e = "ahoj";
    printf("\nLABEL $%s"\
        "\nPUSHFRAME\n", e);
}
