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
#include "AST.h"


int interpret(root *root);

/******************** generovanie funkcii ********************/

void gen_func_begin(root *root, int i);

void gen_func_end(root *root, int i);

void gen_func_call(root *root, int i);

void gen_func_def_arg(int i);

void gen_func_move_arg(root *root, int i, int j);

void gen_func_ret(root *root, int i, int j);

/******************** generovanie instrukcii ********************/

void gen_defvar(root *root, int i);

void gen_move_int(root *root, int i, int a);

void gen_move_string(root *root, int i, int a);

void gen_move_number(root *root, int i, int a);

void gen_move_int_indef(root *root,int i);

void gen_move_string_indef(root *root, int i);

void gen_move_number_indef(root *root,int i);

void gen_move_in_func_call(char *var);

void gen_add(char *first, char *second);

void gen_sub(char *first, char *second);

void gen_mul(char *first, char *second);

void gen_div(char *first, char *second);

void gen_idiv(char *first, char *second);

void gen_LT(char *x);

void gen_GT(char *x);
    
void gen_EQ(char *x);

/******************** generovanie cyklov ********************/

void gen_if();

void gen_else();

void gen_while();

void gen_then();

/******************** generovanie vstavanych funkcii ********************/

void gen_builtin_func(root *root, int i);

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