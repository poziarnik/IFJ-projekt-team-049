#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "MyStackTree.h"



typedef enum{
    LESS_MORE_EQUAL_NOTEQUAL,
    CONCATENATION,
    PLUS_MINUS,
    MULTIPLICATION_DIVISION_INTDIV,
    SIZEOF,
    LEFTBRACKET,
    RIGHTBRACKET,
    DATA,
    ELSE,
    NOTERM, 
}precedenceOperators;


int compare(Token* MyToken, TokenList* list);
int table_input_symbol(Token_type type);
int colomn_table(TStack *Stack);
int stack_operation(TStack *Stack, Token *token, int table[9][9], bool MISS);
int reduce_by_rule(TStack *Stack, Token *token);
int reduce_brackets(TStack *Stack, Token *token);