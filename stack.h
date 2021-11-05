#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 20

typedef struct Symbol {        //token
    char* type;                   //typ tokenu
    char* att;              //bude nutne alokovat pamet
    struct Symbol* next;
}symbol;

typedef struct{
    symbol *mySymbol;
    int topIndex; 
}stack;

