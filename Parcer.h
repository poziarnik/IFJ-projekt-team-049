#include <stdio.h>
#include <stdlib.h>
#include "Scanner.h"
#include "stack.h"

/**
 * @brief 
 * 
 * @param MyToken fgfgdgfd
 * @param list 
 * @return int (vizerror.h)
 *         
 */
int compare(Token* MyToken, TokenList* list);
/**
 * @brief 
 * 
 * @param tokenType 
 * @return int 
 */
int tokenToColumn(char* tokenType);
int topOfStackToLine(stack* MyStack);
void tokenToSymbol(char* tokenType, char* symbol);
int isItRule(char** rules,char* wannaBeRule, stack* MyStack);