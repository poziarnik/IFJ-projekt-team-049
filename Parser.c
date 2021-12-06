#include "Parser.h"

#define PRINT_ON true //ak chces printovat priebeh nastav true ak nie nastav false
/*global function factorial ( n : integer, a : number) : integer , number 
while e do end 21*/
//bacha segfault
int Parse(TokenList* list, ASTtree* abstractTree, symtable* mySymtable){
    int status = 0;
    
    Token* MyToken=(Token*)malloc(sizeof(Token));
    if (MyToken == NULL) return INTERNAL_ERROR;
    
    
    if (status != 0) return status;
    

    status = tokenScan(stdin, list, MyToken);
    if (status == LEXICAL_ERROR) return status; 

    RETURN_ON_ERROR(fc_program);
    //ASTprintStack(abstractTree->ASTStack);
    //printGlobalTree(mySymtable);
    return PARC_TRUE;
}
bool first(Token* MyToken, NonTerminal MyNonTerminal){
    if (MyNonTerminal==program){
        if(first(MyToken, code)){
            return true;
        }
    }
    else if (MyNonTerminal==code){
        if(first(MyToken, functionDec)){
            return true;
        }
    }
    else if (MyNonTerminal==functionDec){
        if (first(MyToken,global_scope)){
            return true;
        }
        else if(MyToken->type==Keyword){
            if(strcmp(MyToken->data.string, "function")==0){
                return true;
            }
        }
    }
    else if(MyNonTerminal==global_scope){
        if(MyToken->type==Keyword){
            if(strcmp(MyToken->data.string, "global")==0){
                return true;
            }
        }
    }
    else if(MyNonTerminal==function_iden){
        if(MyToken->type==Identifier){
            return true;
        }
    }
    else if(MyNonTerminal==params){
        if(first(MyToken, param)){
            return true;
        }
    }
    else if(MyNonTerminal==returnTypes){
        if (MyToken->type==Colon){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==nextType){
        if (MyToken->type==Comma){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==param){
        if (MyToken->type==Identifier){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==nextParam){
        if (MyToken->type==Comma){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==statement){
        if (first(MyToken, condition)){
            return true;
        }
        else if (first(MyToken, loop)){
            return true;
        }
        else if(first(MyToken, define)){
            return true;
        }
        else if (first(MyToken, assigneOrFunctioCall)){
            return true;
        }
        else if(first(MyToken, FCreturn)){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==condition){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"if")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==loop){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"while")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
        
    }
    else if (MyNonTerminal==define){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"local")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else if (MyNonTerminal==assigneOrFunctioCall){
        if (first(MyToken,var)){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==varlist){
        if (first(MyToken,var)){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==var){
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
        
    }
    else if (MyNonTerminal == nextVar){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==expression)
    {
        if(MyToken->type==Identifier){
            return true;
        }
        else if(MyToken->type==Number){
            return true;
        }
        else if(MyToken->type==Integer){
            return true;
        }
        else if(MyToken->type==String){
            return true;
        }
        else if(MyToken->type==Sizeof){
            return true;
        }
        else if(MyToken->type==L_bracket){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal == nextExpression){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==functionCall)
    {
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal == elseCondition)
    {
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"else")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == prolog)
    {
        if(MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"require")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == initialize)
    {
        if (MyToken->type==Assign){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == FCallparams){
        if (first(MyToken,FCallparam)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == FCallparam){
        if (first(MyToken, expression)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == FCallnextParam){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;        
    }
    else if(MyNonTerminal == FCreturn){
        if(MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"return")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if(MyNonTerminal == statementOutOfFc){
        if(first(MyToken, functionCall)){
            return true;
        }
        else if (first(MyToken,functionDec)){
            return true;
        }
        else return false;
        
    }
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!dorobit nejake first

    return false;
}
//ak chyba alebo koniec return ak nie tak nereturnuj nic




    
    


int fc_program(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                  //program: <prolog><code>
    int status = 0;
    if(first(MyToken, prolog)){
        RETURN_ON_ERROR(fc_prolog);
    }
    if(first(MyToken, code)){
        RETURN_ON_ERROR(fc_code);
    }
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_code(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                     //code: <functionDec><code><statement>
    int status = 0;
    if (first(MyToken, functionDec)){
        RETURN_ON_ERROR(fc_functionDec);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, code)){
        RETURN_ON_ERROR(fc_code);
    }

    if (first(MyToken, statementOutOfFc)){
        RETURN_ON_ERROR(fc_statementOutOfFc); 
    }
    
    return PARC_TRUE;
}
int fc_statementOutOfFc(Token* MyToken, TokenList* list, symtable* mySymtable, ASTtree* abstractTree){        //statementOutOfFc: <functionDec>||<functionCall>(bez ids) <statementOutOfFc>
    int status = 0;
    //puts("halooooooooooo");
    if (first(MyToken, functionDec)){
        RETURN_ON_ERROR(fc_functionDec);
    }
    else if (MyToken->type==Identifier){
        RETURN_ON_ERROR_FCCALL(false);
    }
    else PARC_FALSE;

    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statementOutOfFc); 
    }
    
    return PARC_TRUE;
}
int fc_functionDec(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){              //functionDec: <global_scope>function<function_iden>(<params><returntypes>)<statement>end
    int status = 0;
    status = ASTaddFCToTree(abstractTree->ASTStack);//vytvaranie AST
    if (status != 0) return status;

    if (first(MyToken,global_scope)){
        RETURN_ON_ERROR(fc_global_scope);
    }

    if (chackStr(MyToken, list, "function")){
        parcerPrint("function" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if(first(MyToken, function_iden)){
        RETURN_ON_ERROR(fc_functionIden);
    }
    else return PARC_FALSE;

    if (MyToken->type==L_bracket){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, params)){
       RETURN_ON_ERROR(fc_params);
    }

    if (MyToken->type==R_bracket){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
      
    if(first(MyToken, returnTypes)){
        RETURN_ON_ERROR(fc_returnTypes);
    }
    
    if(first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
    
    if (chackStr(MyToken, list, "end")){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);
    /*ASTprintStack(abstractTree->ASTStack);
        printf("\n\n");*/
    return PARC_TRUE;
}
int fc_global_scope(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                   //global_scope: global
    int status = 0;
    if(chackStr(MyToken,list,"global")){
        parcerPrint("global" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    
    return PARC_TRUE;
}
int fc_functionIden(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                   //functionIden: <functionIden>
    int status = 0;
    if (MyToken->type==Identifier){
        status = ASTsaveToken(abstractTree->ASTStack, MyToken, functionID);//vytvaranie AST
        if(status != 0) return status;

        parcerPrint("function_Iden" ,MyToken ,PRINT_ON);
        status = sym_saveFun(&mySymtable->sym_globalTree,&mySymtable->sym_subTree, mySymtable->sym_stack,MyToken->data.string);//vytvaranie symtable
        if (status == INTERNAL_ERROR) return status;

        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }
    return PARC_TRUE;
}
int fc_params(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                         //params: <param><nextParam>
    int status = 0;
    if(first(MyToken, param)){
        RETURN_ON_ERROR(fc_param);
    }
    else{
        return PARC_FALSE;
    }

    if(first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_nextParam);
    }

    /*printf("params: %s\n",MyToken->att);
    tokenScan(stdin, list, MyToken);*/
    return PARC_TRUE;
}
int fc_param(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                          //param: <identifier>:<type>
    int status = 0;
    if(MyToken->type==Identifier){
        //printf("nieco %s\n",MyToken->data.string);
        ASTsaveToken(abstractTree->ASTStack, MyToken, functionParams);//vytvaranie AST
        parcerPrint("identifier" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }   
    else{
        return PARC_FALSE;
    }

    if (chackStr(MyToken, list, ":")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    } 

    if(isTokenDataType(MyToken)){
        int status;
        parcerPrint("param" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
        //return true;
    }
    else{
        return PARC_FALSE;
    }

    return PARC_TRUE;
}
int fc_nextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                      //nextparam: ,<param><nextparam>
    int status = 0;
    if (chackStr(MyToken, list, ",")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }     

    if (first(MyToken, param)){
        RETURN_ON_ERROR(fc_param);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_nextParam);
    }

    return PARC_TRUE;
}
int fc_returnTypes(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                      //returnTypes: :type<nextType>
    int status = 0;
    if (MyToken->type==Colon){
        parcerPrint("return_types start" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;     
    }
    else{
        return PARC_FALSE;
    } 

    if (isTokenDataType(MyToken)){
        status = ASTsaveToken(abstractTree->ASTStack, MyToken, functionReturnTypes);
        if (status != 0) return status;
        
        //printf("Type: %s\n",MyToken->att);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextType)){
        RETURN_ON_ERROR(fc_nextType);
    }
    
    return PARC_TRUE;
}
int fc_nextType(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                            //nextType: ,Type<nextType>
    int status = 0;
    if (chackStr(MyToken, list, ",")){
        parcerPrint("next_type" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (isTokenDataType(MyToken)){
        parcerPrint("type" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    
    }
    if (first(MyToken, nextType)){
        RETURN_ON_ERROR(fc_nextType);
    }

    return PARC_TRUE;
}
int fc_statement(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                              //statemnet: <<loop>||<condition>||<assigne>||<define>> <statment> 
    int status = 0;

    if (first(MyToken, loop)){
        RETURN_ON_ERROR(fc_loop);
    }
    else if (first(MyToken, condition)){
        //ASTprintStack(abstractTree->ASTStack);
        RETURN_ON_ERROR(fc_condition);
        
    }
    else if (first(MyToken, assigneOrFunctioCall)){ 
        if (isFunDeclared(MyToken->data.string, mySymtable->sym_globalTree)){   //ak je funkcia ries function call ak nie ries assigne
            RETURN_ON_ERROR_FCCALL(false); 
        }
        else{ 
            RETURN_ON_ERROR(fc_assigne); 
        }
    }
    else if (first(MyToken, define)){
        RETURN_ON_ERROR(fc_define);
    }
    else if (first(MyToken, FCreturn)){
        RETURN_ON_ERROR(fc_FCreturn);
    }
    else return PARC_FALSE; 
    if (first(MyToken, statement)){
       RETURN_ON_ERROR(fc_statement);  
    }
    
    return PARC_TRUE;
}
int fc_loop(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                    //loop: while<expression>do<statement>end
    int status = 0;

    //vytvaranie symtable
    symNewStackBlock(mySymtable->sym_stack,&mySymtable->sym_subTree); 
    //vytavaranie AST
    status = ASTaddCycleToTree(abstractTree->ASTStack);
    if (status != 0) return status;

    //parsing
    if (chackStr(MyToken, list, "while")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, "do")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }

    if (chackStr(MyToken, list, "end")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);

    return PARC_TRUE;
}
int fc_condition(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                               //condition: if<expresion>then<statement><elseCondition>end
    int status = 0;
    
    //vytvaranie symtable
    symNewStackBlock(mySymtable->sym_stack,&mySymtable->sym_subTree); 
    //vytvaranie AST
    status = ASTaddConditionToTree(abstractTree->ASTStack);
    if (status != 0) return status;

    if (chackStr(MyToken, list, "if")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, "then")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
        
    if(first(MyToken,elseCondition)){
        RETURN_ON_ERROR(fc_elseCondition);
    }

    if (chackStr(MyToken, list, "end")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);
    return PARC_TRUE;
}
int fc_elseCondition(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                               //else<statement>
    int status = 0;
    //vytvaranie symtable
    symNewStackBlock(mySymtable->sym_stack,&mySymtable->sym_subTree); 
    //vytvaranie AST
    status = ASTaddElseToCondition(abstractTree->ASTStack);

    if(status != 0) return status;

    if (chackStr(MyToken, list, "else")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);
    return PARC_TRUE;
}
    
int fc_assigne(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                      //<var><nextVar>=<expresion><nextExpresion>     or varlist=expresionlist
    int status = 0;
    bool assigneOrFCcall=0;//0 - asigne
    
    status = ASTaddAssigmentToTree(abstractTree->ASTStack);//vytvaranie AST
    if(status != 0) return status;

    if (first(MyToken, var)){
        RETURN_ON_ERROR(fc_var);
    }
    else return PARC_FALSE;

    if (first(MyToken, nextVar)){
        RETURN_ON_ERROR(fc_nextVar);
    }
    
    if (MyToken->type==Assign){
        parcerPrint("assign" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;    
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){// or fccall + cash(Token** cash)ked sa rozhodne ci assigne alebo funkcia prida do vytvorenej struktury 
        if(MyToken->type==Identifier){
            if (isFunDeclared(MyToken->data.string, mySymtable->sym_globalTree)){   //ak je funkcia ries function call ak nie ries assigne
                
                ASTdeleteLastFromTree(abstractTree->ASTStack);//odstranim assigneLeaf zo stromu
                
                status = ASTswitchAssigneFCcall(abstractTree->ASTStack);//odstranim assigneLeaf zo stacku. Switch vytvori FCCall na stacku takze do fcCall posielam true aby dvakrat nevytvoril FCCall
                if (status != 0) return status;

                RETURN_ON_ERROR_FCCALL(true);
                assigneOrFCcall=1; 
            }
            else{
                RETURN_ON_ERROR(fc_expression);
            }
        }
        else{
            RETURN_ON_ERROR(fc_expression);
        }
    }
    else return PARC_FALSE;

    if (first(MyToken, nextExpression)){
        RETURN_ON_ERROR(fc_nextExpression);
    }
    
    if(!assigneOrFCcall) ASTendStatement(abstractTree->ASTStack);//ak sa zavolal fccall tak ten sa sam odstrani zo zasobniku
    //puts("im here");
    return PARC_TRUE;
}
int fc_var(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                         //identifier
    int status = 0;
    if(MyToken->type==Identifier){
        if (!isVarDeclared(mySymtable->sym_stack, MyToken->data.string)) return SEMANTICAL_NODEFINITION_REDEFINITION_ERROR;//ak nie je premenna deklarovana vrat 3
        status = ASTaddToTokenArray(&(abstractTree->ASTStack->head->statement->TStatement.assignment->IDs), \
        abstractTree->ASTStack->head->statement->TStatement.assignment->nbID, MyToken);
        if (status != 0) return status;

        parcerPrint("var" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
int fc_nextVar(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                     //,<var><nextVar>
    int status = 0;
    if (chackStr(MyToken, list, ",")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,var)){
        RETURN_ON_ERROR(fc_var);
    }
    else return PARC_FALSE;
    
    if (first(MyToken,nextVar)){
        RETURN_ON_ERROR(fc_nextVar);
    }
    
    return PARC_TRUE;
}
int fc_expression(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                  //Martin Huba
    int status = 0;
    
    Tree* newExpression=(Tree*)malloc(sizeof(Tree));
    if (newExpression == NULL) return INTERNAL_ERROR;

    parcerPrint("expression" ,MyToken ,PRINT_ON);
    //skontroluj expresion
    status=expressionCheck(MyToken,list,newExpression);
    if (status!=0) return status;
    //vloz expression do AST
    if (abstractTree->ASTStack->head->statement->type==ASTcycle){
        *abstractTree->ASTStack->head->statement->TStatement.while_loop->expression=*newExpression;
    }
    else if (abstractTree->ASTStack->head->statement->type==ASTassigne){
        status = ASTaddToExpressions(&(abstractTree->ASTStack->head->statement->TStatement.assignment->expressions), \
                            abstractTree->ASTStack->head->statement->TStatement.assignment->nbexpressions, newExpression);
        if(status != 0) return status;
    }
    else if(abstractTree->ASTStack->head->statement->type==ASTcondition){
        *abstractTree->ASTStack->head->statement->TStatement.if_loop->expression=*newExpression;
    }
    else if (abstractTree->ASTStack->head->statement->type==ASTdefine){
        abstractTree->ASTStack->head->statement->TStatement.definiton->ExFc.expression=(Tree*)malloc(sizeof(Tree));//vo ExFc allokujem pamat pre expression
        if(abstractTree->ASTStack->head->statement->TStatement.definiton->ExFc.expression==NULL) return INTERNAL_ERROR;
        *abstractTree->ASTStack->head->statement->TStatement.definiton->state=Expression;//uloz info o tom ze define obsahuje espression
        *abstractTree->ASTStack->head->statement->TStatement.definiton->ExFc.expression=*newExpression;//uloz nove expression
    }

    return PARC_TRUE;
}
int fc_nextExpression(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                              //,<expresion><nextExpression>
    int status = 0;
    if (chackStr(MyToken, list, ",")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;

    if (first(MyToken,nextExpression)){
        RETURN_ON_ERROR(fc_nextExpression);
    }
    
    return PARC_TRUE;
}
int fc_define(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                        //define: local|identifier:type<inicialize>
    int status = 0;
    status = ASTaddDefineToTree(abstractTree->ASTStack);//vytvaranie AST
    if(status != 0) return status;

    if (chackStr(MyToken, list, "local")){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (MyToken->type==Identifier){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        sym_saveVar(&mySymtable->sym_subTree->tree, MyToken->data.string);

        status = ASTsaveToken(abstractTree->ASTStack, MyToken, definitionID);
        if(status != 0) return status;

        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, list, ":")){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }

    if(isTokenDataType(MyToken)){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        status = ASTsaveToken(abstractTree->ASTStack, MyToken, definitionDataType);
        if (status != 0)return status;
        
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,initialize)){
        RETURN_ON_ERROR(fc_initialize);
    }

    ASTendStatement(abstractTree->ASTStack);
    return PARC_TRUE;
}
int fc_functionCall(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree, bool withIDs){                                 //functionCall: identifier(<FCparams>)
    int status = 0;
  //zatial nie je pouzite(po implementacii symtable pridat do assigne a do define)
    //ASTprintStack(abstractTree->ASTStack);
    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Type %d", abstractTree->ASTStack->head->statement->type);
    
    if (!withIDs){
        status = ASTaddFCcallToTree(abstractTree->ASTStack);
        if (status != 0) return status; 
    }
    if (MyToken->type==Identifier){
        abstractTree->ASTStack->head->statement->TStatement.functioncall->functionName->data.string = MyToken->data.string;
        parcerPrint("functionCall" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
        //kontrola ci definovana funkcia
    }
    
    if (chackStr(MyToken, list, "(")){
        
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,FCallparams)){
        RETURN_ON_ERROR(fc_FCallparams);
    }
    
    if (chackStr(MyToken, list, ")")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    ASTendStatement(abstractTree->ASTStack);
    return PARC_TRUE;
}
int fc_FCallparams(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                         //params: <param><nextParam>
    int status = 0;
    if(first(MyToken, FCallparam)){
        RETURN_ON_ERROR(fc_FCallparam);
    }
    else{
        return PARC_FALSE;
    }
    if(first(MyToken, FCallnextParam)){
        RETURN_ON_ERROR(fc_FCallnextParam);
    }

    return PARC_TRUE;
}
int fc_FCallparam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                          //param: <expression>
    int status = 0;
    if(first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
        /*parcerPrint("functionCall" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;*/
    }   
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_FCallnextParam(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                      //nextparam: ,<param><nextparam>
    int status = 0;
    if (chackStr(MyToken, list, ",")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }     
    if (first(MyToken, FCallparam)){
        RETURN_ON_ERROR(fc_FCallparam);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_FCallnextParam);
    }

    return PARC_TRUE;
}
//dorobit function call !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int fc_initialize(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){                                  //initialize: =<expresion>||<functionCall>
    int status = 0;

    if (chackStr(MyToken, list, "=")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, expression)){                                                //!!!!!or functionCall
        if(MyToken->type==Identifier){
            if(isFunDeclared(MyToken->data.string,mySymtable->sym_globalTree)){
                RETURN_ON_ERROR_FCCALL(false);
            }
            else RETURN_ON_ERROR(fc_expression);
        }
        else RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
  
    return PARC_TRUE;
}

int fc_prolog(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){
    int status = 0;
    if (MyToken->type==Keyword){
        if (chackStr(MyToken, list, "require")){
            parcerPrint("Prolog" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    if (MyToken->type==String){
        if (chackStr(MyToken, list, "ifj21")){
            parcerPrint("Prolog" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
int fc_FCreturn(Token* MyToken,TokenList* list, symtable* mySymtable, ASTtree* abstractTree){          //FCreturn: return (<FCparams>)
    int status = 0;
    if (MyToken->type==Keyword){
        if (chackStr(MyToken, list, "return")){
            parcerPrint("Return" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    if (first(MyToken,FCallparams)){
        RETURN_ON_ERROR(fc_FCallparams);
    }

    return PARC_TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chackType(Token* MyToken, TokenList* list, Token_type checkType){    
    if (MyToken->type==checkType){
        //printf("TypeCheck: %d\n",MyToken->type);
        int status = 0;
        SCAN_TOKEN;
        return PARC_TRUE;
    }
    else{
        return PARC_FALSE;
    }
}

bool compareTokenStr(Token* MyToken, char* Str){
    if((MyToken->type != Number) && (MyToken->type != Integer)){
        if(strcmp(MyToken->data.string, Str)==0){
            return true;
        }
    }
    return false;
}
bool chackStr(Token* MyToken, TokenList* list, char* Str){
    if ((MyToken->type != Number) && (MyToken->type != Integer)){
        
        if (compareTokenStr(MyToken, Str)){
            //printf("StringCheck: %s\n",MyToken->data.string);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    
    
    
}
/*
    je identifikator
*/
bool isTokenDataType(Token* MyToken){
    if(compareTokenStr(MyToken, "integer")){
        return true;
    }
    else if(compareTokenStr(MyToken, "number")){
        return true;
    }
    else if(compareTokenStr(MyToken, "string")){
        return true;
    }
    else if(compareTokenStr(MyToken, "nil")){
        return true;
    }
    else
    {
        return false;
    }
}
void parcerPrint(char* state ,Token* MyToken ,bool on){
    if (on){
        if ( MyToken->type==Integer){
            printf("%s: %d\n",state,MyToken->data.integer);
        }
        else if (MyToken->type==Number){
            printf("%s: %f\n",state,MyToken->data.number);
        }
        else{
            if (strcmp(state,"loop")==0)
            {
                printf("\033[1;33m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"condition")==0){
                printf("\033[0;32m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"assign")==0){
                printf("\033[0;31m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"define")==0){
                printf("\033[0;34m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else
            {
                printf("%s: %s\n",state,MyToken->data.string);
            }
        }
    }
}
void printGlobalTree(symtable* mySymtable){
   printf("\nglobal tree:\n");
    sym_inorder(mySymtable->sym_globalTree); 
}


int global_level_root(){
    Tstate *global = (Tstate*)malloc(sizeof(Tstate));
    if (global == NULL){
        return INTERNAL_ERROR;
    }
    global = NULL;
    return PROGRAM_OK;
}
    
int global_level_function(Tstate *global){
    TFunction_tree *new_global = (TFunction_tree*)malloc(sizeof(TFunction_tree));
    if (new_global == NULL){
        return INTERNAL_ERROR;
    }
    //hodit niake informacie do toho globalu;
    global->TStatement.function = new_global;
    return PROGRAM_OK;
}
/*int isExpressionOrFCcall(symtable* mySymtable, Token* MyToken){
    if(first(MyToken, expression)){
        if (MyToken->type==Identifier){
            if(isFunDeclared(MyToken->data.string,mySymtable->sym_globalTree)) return 1;
        }
        else return 0
    }
}*/
