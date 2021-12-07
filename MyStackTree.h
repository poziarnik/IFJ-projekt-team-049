#ifndef __STACKTREE__

#define __STACKTREE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"
#include "error.h"

/**
 * @brief 
 * 
 */
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

/**
 * @brief Struktura stromu, ktora sa sklada z tokenu a popripade synovskych uzlov
 * 
 */
typedef struct tree{
    Token *Data;
    union {
        struct {
            struct tree *left;
            struct tree *right;
        } binary;
        struct {
            struct tree *child;
        } unary;    
    } attr;
}Tree;

/**
 * @brief Struktura Elementu stacku
 * 
 */
typedef struct Element{
    precedenceOperators Item;
    struct tree *tree;
    struct Element *next;
}TElement;

/**
 * @brief Struktura Stacku
 * 
 */
typedef struct Stack{
    TElement *top;
}TStack;

/**
 * @brief Inicializuje Stack
 * 
 * @param Stack 
 */
void Stack_init(TStack *Stack);

/**
 * @brief pushnem item na Stack
 * 
 * @param Stack 
 * @param newItem 
 * @param token 
 * @return int 
 */
int Stack_push(TStack *Stack, int newItem, Token *token);

/**
 * @brief Pushnem na Stack Element stacku, pouziva sa ked uz nieco v Elemente je nahrate a nechcem to stratit
 * 
 * @param Stack 
 * @param Element 
 */
void Stack_Push_Element(TStack *Stack, TElement *Element);

/**
 * @brief Odstranim element zo stacku
 * 
 * @param Stack 
 */
void Stack_pop(TStack *Stack);

/**
 * @brief Odstrani element zo stacku a vrati jeho adresu
 * 
 * @param stack 
 * @return TElement* 
 */
TElement *stack_pop_nofree(TStack *stack);

/**
 * @brief Vracia prvy terminal na stacku
 * 
 * @param stack 
 * @return int 
 */
int Stack_first_term(TStack *stack);


void Stack_print(TStack *stack);
TElement Stack_top(TStack *stack);
void TreeInit(Tree **tree);

/**
 * @brief uvolni expression Tree
 * 
 * @param exprTree 
 */
void freeExprTree(Tree *exprTree);

#endif // !1