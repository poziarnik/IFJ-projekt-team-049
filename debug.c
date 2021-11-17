#include "debug.h"

char *debug_color_str[] = {
    "\x1B[31m",
    "\x1B[32m",
    "\x1B[33m",
    "\x1B[34m",
    "\x1B[37m",
    "\x1B[36m",
    "\x1B[35m"};

char *debug_keyword_to_str[] = {
    "KEYWORD_TYPE_DO",
    "KEYWORD_TYPE_ELSE",
    "KEYWORD_TYPE_END",
    "KEYWORD_TYPE_FUNCTION",
    "KEYWORD_TYPE_GLOBAL",
    "KEYWORD_TYPE_IF",
    "KEYWORD_TYPE_INTERGER",
    "KEYWORD_TYPE_LOCAL",
    "KEYWORD_TYPE_NIL",
    "KEYWORD_TYPE_NUMBER",
    "KEYWORD_TYPE_REQUIRE",
    "KEYWORD_TYPE_RETURN",
    "KEYWORD_TYPE_STRING",
    "KEYWORD_TYPE_THEN",
    "KEYWORD_TYPE_WHILE",
    "KEYWORD_TYPE_BOOLEAN",
    "KEYWORD_TYPE_AND",
    "KEYWORD_TYPE_OR",
    "KEYWORD_TYPE_NOT",
    "KEYWORD_TYPE_TRUE",
    "KEYWORD_TYPE_FALSE"};

char *debug_token_to_str[] = {
    "TOKEN_TYPE_IDENTIFIER",
    "TOKEN_TYPE_KEYWORD",
    "TOKEN_TYPE_STRING",
    "TOKEN_TYPE_STRING_LENGTH",
    "TOKEN_TYPE_NUMBER",
    "TOKEN_TYPE_NUMBER_DOUBLE",
    "TOKEN_TYPE_BOOLEAN",
    "TOKEN_TYPE_MINUS",
    "TOKEN_TYPE_PLUS",
    "TOKEN_TYPE_MULTIPLY",
    "TOKEN_TYPE_DIVIDE",
    "TOKEN_TYPE_INT_DIVIDE",
    "TOKEN_TYPE_ASSIGN",
    "TOKEN_TYPE_IS_EQUAL",
    "TOKEN_TYPE_NOT_EQUAL",
    "TOKEN_TYPE_LESS_THAN",
    "TOKEN_TYPE_LESS_EQUAL_THAN",
    "TOKEN_TYPE_GREATER_THAN",
    "TOKEN_TYPE_GREATER_EQUAL_THAN",
    "TOKEN_TYPE_LEFT_BRACKET",
    "TOKEN_TYPE_RIGHT_BRACKET",
    "TOKEN_TYPE_COLON",
    "TOKEN_TYPE_CONCAT",
    "TOKEN_TYPE_COMMA",
    "TOKEN_TYPE_EOL",
    "TOKEN_TYPE_EOF"};

char *psa_index_to_str[] = {
    "IDENTIFIER",
    "DOLLAR",

    "IDENTIFIER",
    "HASH",
    "IDENTIFIER",
    "IDENTIFIER",
    "IDENTIFIER",

    "PLUS_MINUS",
    "PLUS_MINUS",
    "MUL_DIV",
    "MUL_DIV",
    "MUL_DIV",
    "DOLLAR",

    "RELATIONS",
    "RELATIONS",
    "RELATIONS",
    "RELATIONS",
    "RELATIONS",
    "RELATIONS",

    "LEFT_BRACKET",
    "RIGHT_BRACKET",
    "DOLLAR",
    "CONCAT",
    "DOLLAR",

    "DOLLAR",
    "DOLLAR"};

char *psa_table_symbol_to_str[] = {
    "HASH",
    "MUL_DIV",
    "PLUS_MINUS",
    "CONCAT",
    "RELATIONS",
    "LEFT_BRACKET",
    "RIGHT_BRACKET",
    "IDENTIFIER",
    "DOLLAR",
    "STOP",
    "NT_E"};

char *debug_psa_index_str(int index) {
    return psa_index_to_str[index];
}

char *debug_symbol_str(PSA_table_symbol symbol) {
    return psa_table_symbol_to_str[symbol];
}

char *debug_keyword_str(Keyword_type type) {
    return debug_keyword_to_str[type];
}

char *debug_token_str(Token_type type) {
    return debug_token_to_str[type];
}

void debug_print(Color_t color, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    fprintf(stdout, "%s", debug_color_str[color]);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, RESET);

    va_end(ap);
}