#include "Scanner.h"

/*
    zatial len skusanie
    getToken vrati slovo oddelene medzerou alebo koncom riadku
    make primitive - preklad bez varovani
    make advanced - preklad s varovaniami
    spustenie - ./test<main.c 
              - cita so stdin tak bz malo ist spusti z hocijakym suborom napr <Scanner.c <Scanner.h whatever
    kontrola s valgrindom - valgrind --leak-check=yes test
*/
int main(){

    /*if(feof == 0){                         neviem ci trba zistovat ci je nieco dane na stdin
        printf("zadaj program k prekladu\n");
        return 0;
    }*/

    TokenList list;
    for (int i = 0; i < 200; i++){
        Token* mytoken = tokenCreate();
        if(mytoken == NULL){
            return 1;
        }
        tokenScan(stdin, &list, mytoken);
    }
    for (Token* i = list.Head; i != NULL; i = i->next)
    {
        printf("%s\n%s\n\n",i->att, i->type);
    }
    listFree(&list);
    
    return 0;
}    