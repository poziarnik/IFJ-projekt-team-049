/**
 *
 * @file generator.c
 * @author Daniel Zalezak
 * @brief
 * @date 
 *
 */

#include "generator.h"
#include "ilist.h"
#include "AST.h"
#include "symtable.h"

#include <stdio.h>
#include <string.h>


int interpret(root *Root){
    printf(".IFJcode21\n");
    if(Root != NULL){
        if(*Root->statements != NULL && Root->nbStatements != NULL){
            for(int i = 0; i < *Root->nbStatements; i++){
                if(Root->statements[i]->type == ASTfunction){   
                    gen_func_begin(Root, i);
                    if(Root->statements[i]->TStatement.function->parameters != NULL){
                        for(int a = 0; a < *Root->statements[i]->TStatement.function->nbParameters ; a++){  
                            gen_func_def_arg(a);
                        }
                        for(int a = 0; a < *Root->statements[i]->TStatement.function->nbParameters ; a++){  
                            gen_func_move_arg(Root,i,a);
                        }
                    }
                    if(*Root->statements[i]->TStatement.function->statements != NULL){   
                        root funcRoot;
                        for(int b = 0; b < *Root->statements[i]->TStatement.function->nbStatements; b++){
                            funcRoot.statements[b] = Root->statements[i]->TStatement.function->statements[b];
                        }
                        funcRoot.nbStatements = Root->statements[i]->TStatement.function->nbStatements;
                        interpret(&funcRoot);
                    }
                    for(int a = 0; a < *Root->statements[i]->TStatement.function->nbReturntypes; a++){
                        gen_func_ret(Root,i, a); 
                    }
                    gen_func_end(Root, i);
                }
                else if(Root->statements[i]->type == ASTcondition){
                    //TODO
                }
                else if(Root->statements[i]->type == ASTcycle){
                    //TODO
                }
                // priradenie cisla / stringu DONE - operacie nie 
                else if(Root->statements[i]->type == ASTassigne){
                    if(Root->statements[i]->TStatement.assignment->nbID == Root->statements[i]->TStatement.assignment->nbexpressions){
                        for(int a = 0; a < *Root->statements[i]->TStatement.assignment->nbID; a++ ){ 
                            if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Integer){    
                                gen_move_int(Root,i, a);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == Number){
                                gen_move_number(Root,i, a);
                            }
                            else if(Root->statements[i]->TStatement.assignment->expressions[a]->Data->type == String){
                                gen_move_string(Root,i, a);
                            }
                        }
                    }
                        
                }
                else if(Root->statements[i]->type == ASTdefine){
                    gen_defvar(Root, i);
                    if(Root->statements[i]->TStatement.definiton->expression != NULL){   
                        // assign
                        
                    }
                }
                // maybe DONE
                else if(Root->statements[i]->type == ASTfunctionCall){
                    if(isInbuildFun((*Root->statements)->TStatement.functioncall->functionName->data.string) == 1){
                        gen_builtin_func(Root,i);
                        if((*Root->statements)->TStatement.functioncall->nbID != 0){
                            for(int a = 0; a < *Root->statements[i]->TStatement.functioncall->nbID; a++){
                                gen_move_in_func_call(Root, i, a);
                            }
                        }
                    }
                    else{
                        gen_func_call(Root, i);                                                                        //prepisat
                        if( Root->statements[i]->TStatement.functioncall->nbID != 0){  
                           for(int a = 0; a < *Root->statements[i]->TStatement.functioncall->nbID; a++){
                                gen_move_in_func_call(Root, i, a);
                            }
                        }
                    }
                }
            }
        }
    }
}

/******************** generovanie funkcii ********************/

void gen_func_begin(root *root, int i){  
        char *func_name = root->statements[i]->TStatement.function->id->data.string;       
        printf("\n LABEL $%s\
                \n CREATEFRAME\
                \n PUSHFRAME\n", func_name);
}

void gen_func_end(root *root, int i){
        char *func_name = root->statements[i]->TStatement.function->id->data.string;
        printf("\nLABEL $%s$end\
                \nPOPFRAME\
                \nRETURN\n", func_name);
}
 

void gen_func_call(root *root, int i){
    printf(" CALL $%s \n", root->statements[i]->TStatement.functioncall->functionName->data.string);
    
}

void gen_func_def_arg(int i){
    printf(" DEFVAR LF@%d", i);
}

void gen_func_move_arg(root *root, int i, int a){
    printf(" MOVE LF@%s", root->statements[i]->TStatement.function->parameters[a]->data.string );
    
}

void gen_func_ret(root *root, int i, int a){
    printf(" POPS LF@return%s \n", root->statements[i]->TStatement.function->returnTypes[a]->data.string);
} 

/******************** generovanie instrukcii ********************/

void gen_defvar(root *root, int i){
    printf("\n DEFVAR LF@%s", root->statements[i]->TStatement.definiton->id->data.string);
    
}

void gen_move_int(root *root,int i, int a){ 
    printf(" \n MOVE LF@%s LF@%d", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.integer );
    
}

void gen_move_string(root *root, int i, int a){ 
    printf(" \n MOVE LF@%s LF@%s", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.string );
}

void gen_move_number(root *root,int i,  int a){ 
    printf(" \n MOVE LF@%s LF@%f", root->statements[i]->TStatement.assignment->IDs[a]->data.string, root->statements[i]->TStatement.assignment->expressions[a]->Data->data.number);
}

void gen_move_in_func_call(root *root, int i, int a){                             
    printf("\n MOVE  LF@%s TF@retval" , root->statements[i]->TStatement.functioncall->IDs[a]->data.string );   
}


void gen_add(char *x){
    printf("\n ADD      LF@retval LF@%s LF@%s" ,x, x);
}

void gen_sub(char *x){
    printf("\n SUB      LF@retval LF@%s LF@%s", x, x);
}

void gen_mul(char *x){
    printf("\n MUL      LF@retval LF@%s LF@%s" ,x, x);
}

void gen_div(char *x){
    printf("\n DIV      LF@retval LF@%s LF@%s", x, x);
}

void gen_idiv(char *x){
    printf("\n IDIV     LF@retval LF@%s LF@%s", x, x);
}

void gen_LT(char *x){
    printf("\n LT       LF@retval LF@%s LF@%s", x, x);
}

void gen_GT(char *x){
    printf("\n GT       LF@retval LF@%s LF@%s", x, x);
}

void gen_EQ(char *x){
    printf("\n EQ       LF@result LF@%s LF@%s", x, x);
}

/******************** generovanie cyklov ********************/

void gen_if(){
//TODO
}

void gen_else(){
//TODO
}

void gen_while(){
//TODO
}

void gen_then(){
//TODO
}

/******************** generovanie vstavanych funkcii ********************/

void gen_builtin_func(root *root, int i){
    switch(*root->statements[i]->TStatement.functioncall->functionName->data.string){ 
        case readi:
            
            gen_read_i();
            break;

        case reads:
            gen_read_s();
            break;

        case readn:
            gen_read_n();
            break;

        case write:
            gen_write();
            break;

        case tointeger:
            gen_f2i();
            break;

        case substr:
            gen_substr();
            break;

        case ord:
            gen_ord();
            break;

        case chr:
            gen_chr();
            break;

        default:
            break;
    }
}

int gen_read_i(){
    printf("\n LABEL        $readi\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval0\
            \n DEFVAR       LF@retval1\
            \n MOVE         LF@retval1 int@0\
            \n DEFVAR       LF@typeout\
            \n READ         LF@retval0 int\
            \n TYPE         LF@typeout LF@retval0\
            \n JUMPIFEQ     $readi$istrue LF@typeout string@int\
            \n MOVE         LF@retval0 int@1\
            \n MOVE         LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\
            \n LABEL        $readi$istrue\
            \n POPFRAME\
            \n RETURN\n");   
}

int gen_read_s(){
    printf("\n LABEL        $reads\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval0\
            \n DEFVAR       LF@retval1\
            \n MOVE         LF@retval1 int@0\
            \n READ         LF@retval0 string\
            \n JUMPIFNEQ    $reads$noerr LF@retval0 nil@nil\
            \n MOVE         LF@retval1 int@1\
            \n LABEL        $reads$noerr\
            \n POPFRAME\
            \n RETURN\n");
}

int gen_read_n(){
    printf("\n LABEL        $readn\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval0\
            \n DEFVAR       LF@retval1\
            \n MOVE         LF@retval1 int@0\
            \n DEFVAR       LF@typeout\
            \n READ         LF@retval0 float\
            \n TYPE         LF@typeout LF@retval0\
            \n JUMPIFEQ     $readn$istrue LF@typeout string@float\
            \n MOVE         LF@retval0 float@0x1p+0\
            \n MOVE         LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\
            \n LABEL        $readn$istrue\
            \n POPFRAME\
            \n RETURN\n");
}

void gen_write(){
    printf("\n LABEL $write\
            \n PUSHFRAME\
            \n");
            //TODO
}

void gen_f2i(){
    printf("\n LABEL        $tointeger\
            \n PUSHFRAME\
            \n DEFVAR       LF@param\
            \n DEFVAR       LF@retval\
            \n FLOAT2INT    LF@retval LF@param\
            \n POPFRAME\
            \n RETURN\n");
}

/*void gen_i2f(){
    printf("\n LABEL        $tofloat\
            \n PUSHFRAME\
            \n DEFVAR       LF@param\
            \n DEFVAR       LF@retval\
            \n INT2FLOAT    LF@retval LF@param\
            \n POPFRAME\
            \n RETURN\n");
}*/



void gen_substr(){
//TODO
}

void gen_ord(){
//TODO
}

void gen_chr(){
    printf("\n LABEL        $chr\
            \n PUSHFRAME\
            \n DEFVAR       LF@retval1\
            \n DEFVAR       LF@retval0\
            \n GT           LF@retval1 LF@param0 int@255\
            \n JUMPIFEQ     $chr$error LF@retval1 bool@true\
            \n LT           LF@retval1 LF@param0 int@0\
            \n JUMPIFEQ     $chr$error LF@retval1 bool@true\
            \n INT2CHAR     LF@retval0 LF@param0\
            \n MOVE         LF@retval1 int@0\
            \n POPFRAME\
            \n RETURN\
            \n LABEL        $chr$error\
            \n MOVE         LF@retval0 string@\
            \n MOVE         LF@retval1 int@1\
            \n POPFRAME\
            \n RETURN\n");
}

/*int main(){                     //test
    
    gen_i2f();
    gen_read_i();
    gen_chr();
    gen_f2i();
    gen_read_n();
    gen_read_s();

    char *x = "ahoj";

    gen_defvar(x);

    gen_move(x);

    gen_add(x);

    gen_sub(x);

    gen_mul(x);

    gen_div(x);

    gen_idiv(x);

    gen_LT(x);

    gen_GT(x);
        
    gen_EQ(x);
}*/

int main(root *test){
    
    int a  = interpret(test);
    
    
}
