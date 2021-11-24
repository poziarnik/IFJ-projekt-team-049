/**
*
* @file ilist.h
* @author Daniel Zalezak
* @brief Header of ilist
* @date 
*
*/


#ifndef _ILIST_H_
#define _ILIST_H_


/*
#define I_STOP    0
#define I_READ    1
#define I_WRITE   2
#define I_SETZERO 3
#define I_INC     4
#define I_DEC     5
#define I_NOT     6
#define I_LAB     7
#define I_IFGOTO  8
#define I_GOTO    9
*/


#define I_MOVE            1
#define I_CRETE_F         2
#define I_PUSH_F          3
#define I_POP_F           4
#define I_DEF_VAR         5
#define I_CALL            6
#define I_RETURN          7

#define I_PUSH_S          8
#define I_POP_S           9
#define I_CLEAR_S         10

#define I_ADD             11
#define I_SUB             12
#define I_MUL             13
#define I_DIV             14
#define I_DIV_INT         15

/* #define I_ADD_S           16
#define I_SUB_S           17
#define I_MUL_S           18
#define I_DIV_S           19
#define I_DIV_INT_S       20 */

#define I_LT              21
#define I_GT              22
#define I_EQ              23

/*#define I_LT_S            24
#define I_GT_S            25
#define I_EQ_S            26 */

#define I_AND             27
#define I_OR              28
#define I_NOT             29

/*#define I_AND_S           30
#define I_OR_S            31
#define I_NOT_S           32 */

#define tofloat             33     // INT TO FLOAT
#define tointeger            34    // FLOAT TO INT
#define I_I2C             35    // INT TO CHAR
#define I_S2I             36    // STRING TO INT

/* #define I_I2F_S           37      // INT TO FLOAT
#define I_F2I_S           38      // FLOAT TO INT
#define I_I2C_S           39      // INT TO CHAR
#define I_S2I_S           40      // STRING TO INT */

#define readi           41
#define reads           42
#define readn          43
#define write           44

#define I_CONCAT          45
#define I_STRLEN          46
#define I_GETCHAR         47
#define I_SETCHAR         48

#define I_TYPE            49

#define I_LABEL           50
#define I_JUMP            51
#define I_JUMP_IF_EQ      52
#define I_JUMP_IF_NEQ     53

#define I_JUMP_IF_EQ_S    54
#define I_JUMP_IF_NEQ_S   55

#define I_EXIT            56

#define I_BREAK           57
#define I_DPRINT          58



typedef struct param {
  char *id;
  int *par_num;
  struct param *next;
} tParam;


typedef struct func{
  struct param *param;
  char *start;
  char *end;
  char *type;
  int *retval;
}tFunc;











/*typedef struct
{
  int instType;  
  void *addr1; 
  void *addr2; 
  void *addr3; 
} tInstr;

typedef struct listItem
{
  tInstr Instruction;
  struct listItem *nextItem;
} tListItem;
    
typedef struct
{
  struct listItem *first;  
  struct listItem *last;   
  struct listItem *active; 
} tListOfInstr;

void listInit(tListOfInstr *L);
void listFree(tListOfInstr *L);
void listInsertLast(tListOfInstr *L, tInstr I);
void listFirst(tListOfInstr *L);
void listNext(tListOfInstr *L);
void listGoto(tListOfInstr *L, void *gotoInstr);
void *listGetPointerLast(tListOfInstr *L);
tInstr *listGetData(tListOfInstr *L);
*/

#endif