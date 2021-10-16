#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct MyToken {        //token
    char* type;                   //typ tokenu
    char* att;              //bude nutne alokovat pamet
}Token;

/*
    typy tokenov
    0 - key word
    1 - integer
    2 - number
    3 - sting
    4 - operator
*/

int getToken( FILE* Myfile, Token* MyToken);
Token* createToken();
void tokenInit(Token* MyToken);
void tokenFullup(Token* MyToken, char* type, char* att);
char* createStr();
char* addToString(char** MyString, int newCharacter, int* sizeOfStr, int* charNb);
void magnifyStr(char** MyString, int sizeOfStr);
int isKeyword(char *word);
