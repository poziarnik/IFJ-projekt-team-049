#include <stdio.h>
#include <stdlib.h>

typedef struct Symbol {        //token
    char* type;                   //typ tokenu
    char* att;              //bude nutne alokovat pamet
    struct Symbol* next;
}symbol;

typedef struct list{
    symbol* head;
}stack;

