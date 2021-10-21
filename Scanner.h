#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct MyToken {        //token
    char* type;                   //typ tokenu
    char* att;              //bude nutne alokovat pamet
    struct MyToken* next;
}Token;

typedef struct list{
    Token* Head;
}TokenList;
/*
    typy tokenov
    0 - key word
    1 - integer
    2 - number
    3 - sting
    4 - operator
*/

int tokenScan( FILE* Myfile, TokenList* list, Token* MyToken);
Token* tokenCreate();
void tokenInit(Token* MyToken);
void tokenFullup(Token* MyToken, char* type, char* att);
char* stringCreate();
char* stringAddChar(char** MyString, int newCharacter, int* sizeOfStr, int* charNb);
int isKeyword(char *word);
void listInit(TokenList* list);
void listAddToken(TokenList* list, Token* NewToken);
void listFree(TokenList* list);
