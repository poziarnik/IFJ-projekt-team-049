#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    Pass_to_object,
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
    Scanner_state_comment_block_end2,
    Scanner_state_plus,
    Scanner_state_multiplication,
    Scanner_state_concatenation,
    Scanner_state_sizeof,
    Scanner_state_division,
    Scanner_state_division_int,
    Scanner_state_less,
    Scanner_state_less_equal,
    Scanner_state_more,
    Scanner_state_more_equal,
    Scanner_state_assign,
    Scanner_state_isequal,
    Scanner_state_notequal,
    Scanner_state_notequal_end,
    Scanner_state_lBracket,
    Scanner_state_rBracket,
    Scanner_state_pass_to_object,
}Scanner_state;

/**
 * @brief Struktura Tokenu, ktora berie typ a 
 * 
 */
typedef struct MyToken {        //token
    Token_type type;                   //typ tokenu
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
void tokenFullup(Token* MyToken, Token_type type, char* att);
char* stringCreate();
char* stringAddChar(char** MyString, int newCharacter, int* sizeOfStr, int* charNb);
int isKeyword(char *word);
int isEscapeSeq(int symbol);
void listInit(TokenList* list);
void listAddToken(TokenList* list, Token* NewToken);
void listFree(TokenList* list);
