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

/******************** generovanie funkcii ********************/

void gen_func_begin(char *id);

void gen_func_end();

void gen_func_call(char *id);

void gen_func_def_arg(/*TODO*/);

void gen_func_move_arg(/*TODO*/);

void gen_func_ret(int ret);

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

void gen_substr();

void gen_ord();

void gen_chr();

#endif