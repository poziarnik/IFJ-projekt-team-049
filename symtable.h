/**
 *
 * @file symtable.h
 * @author Daniel Zalezak
 * @brief Header of symtable
 * @date 
 *
 */

#ifndef symtable_h
#define symtable_h


typedef struct {
    int varType;
}tData;

typedef struct tableItem {
    char key;
    tData data;
    struct tableItem *lptr;
    struct tableItem *rptr;
} tTableItem;

typedef struct tSymbolTable {
    struct tableItem *root;
} tSymbolTable;

void tableInit(tSymbolTable *T);

#endif