//s aadddsa

#include <stdio.h>
#include <stdlib.h>
#include "Scanner.h"
#include "stack.h"

int compare(Token* MyToken, TokenList* list);
int symbolToColumn(char* tokenType);
int topOfStackToLine(stack* MyStack);
void tokenToSymbol(char* tokenType, char* symbol);
int isItRule(char** rules,char* wannaBeRule);