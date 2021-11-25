/**
 *
 * @file generator.h
 * @author Daniel Zalezak
 * @brief
 * @date 
 *
 */

#ifndef generator_h
#define generator_h

#include "symtable.h"
#include "ilist.h"


int interpret(tFunc *function);

/******************** generovanie funkcii ********************/

void gen_func_begin(tFunc *function);

void gen_func_end(tFunc *function);

void gen_func_call(char *id);

void gen_func_def_arg(tFunc *function);

void gen_func_move_arg(tFunc *function);

void gen_func_ret(tFunc *function);

/******************** generovanie operacii ********************/

void gen_defvar(char *x);

void gen_move(char *x);

void gen_add(char *x);

void gen_sub(char *x);

void gen_mul(char *x);

void gen_div(char *x);

void gen_idiv(char *x);

void gen_LT(char *x);

void gen_GT(char *x);
    
void gen_EQ(char *x);

/******************** generovanie cyklov ********************/

void gen_if();

void gen_else();

void gen_while();

void gen_then();

/******************** generovanie vstavanych funkcii ********************/

void gen_builtin_func();

int gen_read_i();

int gen_read_s();

int gen_read_n();

void gen_write();

void gen_f2i();

void gen_i2f();

void gen_substr();

void gen_ord();

void gen_chr();

#endif