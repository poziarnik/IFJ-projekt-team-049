#ifndef __PARSER__

#define __PARSER__

#include <stdio.h>
#include <stdlib.h>
#include "MyStackTree.h"
#include "symtable.h"

typedef enum{
    INT,
    INT_zero,
    NR,
    NR_zero,
    STR,
    STR_zero,
    NIL,
}expressionType;




/**
 * @brief Print expression stromu
 * 
 * @param exprtree -strom
 */

void printExpressionTree(Tree *exprtree);
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

int isExpresionright(Tree *exprTree);

int expressionSemanticCheck(Tree *exprTree);

#endif // !__PARSER__