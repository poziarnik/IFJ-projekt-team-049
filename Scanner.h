#ifndef _SCANNER_
#define _SCANNER_ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Mnozina typu tokenov
 * 
 */
typedef enum{
    Identifier,
    Keyword,
    Integer,
    Number,
    String,
    Minus,
    Plus,
    Multiplication,
    Concatenation,
    Sizeof,
    Division,
    Division_integer,
    Less,
    Less_equal,
    More,
    More_equal,
    Assign,
    Is_equal,
    Not_equal,
    L_bracket,
    R_bracket,
    Colon,
    Comma,
    End_of_file,
}Token_type;

/**
 * @brief Mnozina stavov automatu
 * 
 */
typedef enum{
    Scanner_state_reading,
    Scanner_state_identifier_1,
    Scanner_state_identifier_2,
    Scanner_state_number_1,
    Scanner_state_number_2,
    Scanner_state_number_3,
    Scanner_state_number_4,
    Scanner_state_number_5,
    Scanner_state_number_6,
    Scanner_state_string_start,
    Scanner_state_string_end,
    Scanner_state_string_1,
    Scanner_state_string_2,
    Scanner_state_string_3,
    Scanner_state_minus,
    Scanner_state_comment_start,
    Scanner_state_comment_block,
    Scanner_state_comment_block_start,
    Scanner_state_comment_block_end1,
    Scanner_state_concatenation,
    Scanner_state_division,
    Scanner_state_less,
    Scanner_state_more,
    Scanner_state_assign,
    Scanner_state_isequal,
    Scanner_state_notequal,
}Scanner_state;

/**
 * @brief Struktura Tokenu, ktora berie typ a 
 * 
 */
typedef struct MyToken {        //token
    Token_type type;            //typ tokenu
    
    union{
        int integer;
        double number;
        char *string;
    }data;
                  
    struct MyToken* next;
}Token;

typedef struct list{
    Token* Head;
}TokenList;


/**
 * @brief Funkcia, ktora vrati token
 * 
 * @param Myfile 
 * @param list 
 * @param MyToken 
 * @return int 
 */
int tokenScan( FILE* Myfile, TokenList* list, Token* MyToken);


Token* tokenCreate();


void tokenInit(Token* MyToken);


void tokenFullup(Token* MyToken, Token_type type, char* att);


char* stringCreate();


char* stringAddChar(char** MyString, int newCharacter, int* sizeOfStr, int* charNb);

/**
 * @brief funkcia kontrolujuca ci je zadany retazec keyword
 * 
 * @param word 
 * @return int 
 */
int isKeyword(char *word);

/**
 * @brief funkcia kontrolujuca ci je zadana sekvencia validna
 * 
 * @param symbol 
 * @return int 
 */
int isEscapeSeq(int symbol);
void listInit(TokenList* list);
void listAddToken(TokenList* list, Token* NewToken);
void listFree(TokenList* list);

#endif //_SCANNER_