#ifndef __PARSER__

#define __PARSER__

#include <stdio.h>
#include <stdlib.h>
#include "MyStackTree.h"






int expressionCheck(Token* MyToken, TokenList* list);
int table_input_symbol(Token *Mytoken);
int colomn_table(TStack *Stack);
int stack_operation(TStack *Stack, Token *token, int table[9][9], bool MISS);
int reduce_by_rule(TStack *Stack);

#endif // !__PARSER__