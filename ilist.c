/**
*
* @file ilist.c
* @author Daniel Zalezak
* @brief  ilist
* @date 
*
*/


#include <stdio.h>
#include <malloc.h>
#include "ilist.h"

/*void listInit(tListOfInstr *L)
{
  L->first  = NULL;
  L->last   = NULL;
  L->active = NULL;
}
  
void listFree(tListOfInstr *L)
{
  tListItem *ptr;
  while (L->first != NULL)
  {
    ptr = L->first;
    L->first = L->first->nextItem;
    free(ptr);
  }
}

void listInsertLast(tListOfInstr *L, tInstr I)
{
  tListItem *newItem;
  newItem = malloc(sizeof (tListItem));
  newItem->Instruction = I;
  newItem->nextItem = NULL;
  if (L->first == NULL)
     L->first = newItem;
  else
     L->last->nextItem=newItem;
  L->last=newItem;
}

void listFirst(tListOfInstr *L)
{
  L->active = L->first;
}

void listNext(tListOfInstr *L)
{
  if (L->active != NULL)
  L->active = L->active->nextItem;
}

void listGoto(tListOfInstr *L, void *gotoInstr) //*
{
  L->active = (tListItem*) gotoInstr;
}

void *listGetPointerLast(tListOfInstr *L) //*
{
  return (void*) L->last;
}

tInstr *listGetData(tListOfInstr *L)
{
  if (L->active == NULL)
  {
    printf("Chyba, zadna instrukce neni aktivni");
    return NULL;
  }
  else return &(L->active->Instruction);
}

*/
