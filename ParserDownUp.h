#ifndef __PARSER__

#define __PARSER__

#include <stdio.h>
#include <stdlib.h>
#include "MyStackTree.h"
#include "symtable.h"
#include "AST.h"

typedef enum{
    INT,
    INT_zero,
    NR,
    NR_zero,
    STR,
    STR_zero,
    NIL,
    UNDEFINED_VARIABLE,
}expressionType;





int expressionCheck(Token* MyToken, TokenList* list, Tree *expression);

/**
 * @brief Podla tokenu rozhodne, typ vstupu to je
 * 
 * @param Mytoken 
 * @return int 
 */
int table_input_symbol(Token *Mytoken);

/**
 * @brief  ak je z tabulky vybrane 'R' alebo 'U' zacnem redukovat podla pravidiel
 * 
 * @param Stack 
 * @param MyToken 
 * @return int 
 */
int reduce_by_rule(TStack *Stack, Token *MyToken);

int isExpresionright(Tree *exprTree, symtable *Symtable);

int expressionSemanticCheck(Tree *exprTree, symtable *Symtable);

#endif // !__PARSER__