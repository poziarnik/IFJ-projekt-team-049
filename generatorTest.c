#include "generator.h"
#include "ilist.h"
#include "AST.h"
#include "Scanner.h"
#include "MyStackTree.h"
#include "symtable.h"
#include "generatorTest.h"

#include <stdio.h>
#include <string.h>

int main(root *test){
    *test->nbStatements = 1;
    //test->statements[0]->type = ASTfunction;
    //test->statements[1]->type = 
    test->statements[0]->type = ASTfunctionCall;
    test->statements[0]->TStatement.functioncall->functionName->data.string = "funkciaa";
    int a = interpret(test);
    
    
}