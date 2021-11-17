#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "expression.h"
#include "scanner.h"

#define RESET "\x1B[0m"

#ifdef __DEBUG_PRINT

#define PRINT_TOKEN_TYPE(_token) \
    debug_print(COLOR_BLUE, "\t%s\n", ((_token) == NULL) ? "<token null>" : debug_token_str((_token)->type))

#define PRINT_KEYWORD_TYPE(_token) \
    debug_print(COLOR_CYAN, "\t%s\n", ((_token) == NULL) ? "<token null>" : debug_keyword_str((_token)->attr.keyword))

#define PRINT_VAR_VALUE(_var) \
    debug_print(COLOR_YELLOW, "\t%s -> %u\n", (#_var), (_var))

#define PRINT_RETURN_VALUE(_var, _rule) \
    debug_print(((_var) != SUCCESS) ? COLOR_RED : COLOR_GREEN, "RETURN VALUE <%s> -> %d\n", (_rule), (_var))

#define PRINT_ERROR_VALUE(_var) \
    debug_print(COLOR_RED, "RETURN VALUE parse() -> %d\n", (_var))

#define PRINT_STACK_SYMBOL(_stack) \
    debug_print(COLOR_MAGENTA, "\t%s : TOP SYMBOL -> %s\n", (#_stack), stack_is_empty((_stack)) ? "<empty>" : debug_symbol_str(stack_top((_stack))->symbol))

#define PRINT_PSA_SYMBOL(_token) \
    debug_print(COLOR_MAGENTA, "\tPSA SYMBOL -> %s\n", (((_token) == NULL)) ? "<null token>" : debug_psa_index_str((_token)->type))

#define PRINT_RULE(_rule) \
    debug_print(COLOR_WHITE, "<%s>\n", (_rule))

#define PRINT_SYMBOL(_symbol) \
    debug_print(COLOR_MAGENTA, "\tPSA SYMBOL -> %s\n", debug_symbol_str((_symbol)))

#else

#define PRINT_RULE(_rule)
#define PRINT_TOKEN_TYPE(_token)
#define PRINT_KEYWORD_TYPE(_token)
#define PRINT_VAR_VALUE(_var)
#define PRINT_RETURN_VALUE(_var, _rule)
#define PRINT_ERROR_VALUE(_var)
#define PRINT_STACK_SYMBOL(_stack)
#define PRINT_SYMBOL(_symbol)
#define PRINT_PSA_SYMBOL(_token)

#endif

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_WHITE,
    COLOR_CYAN,
    COLOR_MAGENTA
} Color_t;

char *debug_keyword_str(Keyword_type type);
char *debug_token_str(Token_type type);
char *debug_symbol_str(PSA_table_symbol);
char *debug_psa_index_str(int);
void debug_print(Color_t color, const char *fmt, ...);

#endif  // __DEBUG_H