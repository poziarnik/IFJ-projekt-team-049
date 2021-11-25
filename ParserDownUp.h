#ifndef __PARSER__

#define __PARSER__

#include <stdio.h>
#include <stdlib.h>
#include "MyStackTree.h"






<<<<<<< HEAD
int compare(Token* MyToken, TokenList* list);
int table_input_symbol(Token *MyToken);
=======
int expressionCheck(Token* MyToken, TokenList* list);
int table_input_symbol(Token_type type);
>>>>>>> 37a55b6ed32f56c1a0761d263ab68feacba705f7
int colomn_table(TStack *Stack);
int stack_operation(TStack *Stack, Token *token, int table[9][9], bool MISS);
int reduce_by_rule(TStack *Stack);
int reduce_brackets(TStack *Stack, Token *token);

#endif // !__PARSER__