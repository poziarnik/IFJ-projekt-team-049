#include<stdio.h>
#include<stdlib.h>

typedef struct MyToken {        //token
    int type;                   //typ tokenu
    char* content;              //bude nutne alokovat pamet
}Token;

/*
    typy tokenov
    0 - key word
    1 - integer
    2 - number
    3 - sting
    4 - operator
*/

Token getToken( FILE Myfile, int counter);

/*
    parametre:
    FILE MyFile - citany subor
    int counter - sucastne miesto v subore
*/
