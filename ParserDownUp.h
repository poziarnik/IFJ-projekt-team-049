//s aadddsa

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "Mystack.h"

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
}precedenceOperators;

typedef enum{
    R, // POP
    L, // PUSH
    E, // ERROR
    I, // EQUAL
}tableItems;







int compare(Token* MyToken, TokenList* list);
int line_table(Token_type type);
int colomn_table(TStack *Stack);
void check_rule(TStack *Stack);
void full_Stack(TStack *Stack, Token *token, int table[9][9]);
