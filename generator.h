/**
 *  Projekt : Implementace prekladace imperativniho jazyka IFJ21
 * @file generator.h
 * @author Daniel Zalezak (xzalez01)
 * @brief generovanie kodu
 *  
 *
 */

#ifndef generator_h
#define generator_h

#include "symtable.h"
#include "AST.h"


int interpret(root *root);

/******************** generovanie funkcii ********************/

void gen_func_begin(root *root, int i);

void gen_func_end(root *root, int i);

void gen_func_call(root *root, int i);

void gen_func_def_arg(root *root, int i, int a);

void gen_func_ret(root *root, int i);

/******************** generovanie instrukcii ********************/

void gen_defvar(root *root, int i);

void gen_move_int(char *var, int i);

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

void gen_strlen(char *string);

void gen_LT(char *first, char *second);

void gen_GT(char *first, char *second);

void gen_EQ(char *first, char *second);
    
void gen_JUMPIFEQ(char *jump ,char *first, char *second);

void gen_JUMPIFNEQ(char *jump ,char *first, char *second);

void gen_OR(char *first, char *second);

/******************** generovanie cyklov ********************/

void gen_then(int counter);

void gen_else(int counter);

void gen_jump_end(int counter);

void gen_end(int counter);

void gen_while(int i);

void gen_while_end(int i);

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
