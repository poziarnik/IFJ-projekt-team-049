#ifndef __PARSER__

#define __PARSER__

#include <stdio.h>
#include <stdlib.h>
#include "MyStackTree.h"




/**
 * @brief Print expression stromu
 * 
 * @param exprtree -strom
 */
void printTree(Tree *exprtree);

/**
 * @brief hlavna funkcia, ktora vytvara vyraz
 * 
 * @param MyToken 
 * @param list 
 * @param expression 
 * @return int 
 */
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

#endif // !__PARSER__