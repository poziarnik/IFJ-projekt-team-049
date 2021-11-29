#ifndef _AST
#define _AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Scanner.h"
#include "MyStackTree.h"

/*typedef struct aststack{
    struct ast_stackElement head
};

typedef struct ast_stackElement{
    struct ast_stackElement next;

}*/

typedef struct root{
    struct state **global_state;
}TRoot;

typedef struct state{
    union statement{
        struct function_tree *function;
        struct if_tree *if_loop; 
        struct while_tree *while_loop;
        //struct assign_tree *assignment;
        struct definition_tree *definiton;
        //struct functioncall_tree *functioncall;
    }TStatement;
}Tstate;

typedef struct function_tree{
    char *id;                       //token->data.string??
    char **parameter;               //token->data.string??
    char **return_type;             //token->data.string??
    struct state **statements;
}TFunction_tree;

typedef struct if_tree{
    Tree *expression;
    struct state **then_statement;
    struct state **else_statement;
}TIf_tree;

typedef struct while_tree{
    Tree *expression;
    struct state **do_statement;
}TWhile_tree;

/*typedef struct assign_tree{
    //TODO
}TAssign_tree;*/

typedef struct definition_tree{
   char *id;
   char **data_type;
   char **value;
}TDefinition_tree;





#endif 