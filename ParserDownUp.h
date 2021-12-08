/**
 * Projekt : Implementace prekladace imperativniho jazyka IFJ21
 * @file ParserDownUp.h
 * @brief Zpracovanie vyrazov a semanticka kontrola vyrazov
 * @author Jakub Skunda (xskund02)
 * 
 */

#ifndef __PRECEDENCEPARSER__
#define __PRECEDENCEPARSER__

#include <stdio.h>
#include <stdlib.h>
#include "MyStackTree.h"
#include "symtable.h"
#include "AST.h"

/**
 * @brief typ pouzity, pri analyze ci je expression validny, alebo nie
 * @brief neskor som pridal 5 prazdnych stavov, lebo som si uvedomil, ze od 6-9 su chybove hodnoty
 * 
 */
typedef enum{
    INT,
    INT_zero,
    NR,
    UNUSED_STATE1,
    UNUSED_STATE2,
    UNUSED_STATE3,
    UNUSED_STATE4,
    UNUSED_STATE5,
    UNUSED_STATE6,
    UNUSED_STATE7,
    UNUSED_STATE8,
    NR_zero,
    STR,
    STR_zero,
    NIL,
    UNDEFINED_VARIABLE,
}expressionType;




/**
 * @brief Vypisovanie expression stromu
 * 
 * @param exprtree -strom
 */

void printExpressionTree(Tree *exprtree);

/**
 * @brief hlavna funkcia, ktora podla tabulky urcuje ci mam vyraz redukovat, popripade expandovat
 * 
 * @param MyToken
 * @param expression 
 * @return int 
 */
int expressionCheck(Token* MyToken, Tree *expression);

/**
 * @brief Podla tokenu rozhodne, ktory typ vstupu to je
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

/**
 * @brief vracia ci je vyraz spravny, popripade chybu
 * 
 * @param exprTree 
 * @param Symtable 
 * @return int 
 */
int isExpresionright(Tree *exprTree, symtable *Symtable);

/**
 * @brief prechadza strom, vykonava semanticku kontrolu vo vyraze
 * 
 * @param exprTree 
 * @param Symtable 
 * @return int 
 */
int expressionSemanticCheck(Tree *exprTree, symtable *Symtable);

/**
 * @brief pomocna funkcia, ktora vrati chybu, ak sa uz chyba vyskytla v synovskych uzloch
 * 
 * @param leftsubtree 
 * @param rightsubtree 
 * @return int 
 */
int treeMistakes(int leftsubtree, int rightsubtree);

#endif // !__PARSER__