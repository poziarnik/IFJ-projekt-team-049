#include "Scanner.h"
#include "error.h"

/*
    zatial len skusanie
    getToken vrati slovo oddelene medzerou alebo koncom riadku
    make primitive - preklad bez varovani
    make advanced - preklad s varovaniami
    spustenie - ./test<main.c 
              - cita so stdin tak bz malo ist spusti z hocijakym suborom napr <Scanner.c <Scanner.h whatever
    kontrola s valgrindom - valgrind ./test<linux
*/
int main(){

    /*if(feof == 0){                         neviem ci trba zistovat ci je nieco dane na stdin
        printf("zadaj program k prekladu\n");
        return 0;
    }*/

    TokenList list;
    listInit(&list);
    int end=0;
    while(end!=10){
        Token* mytoken = tokenCreate();
        if(mytoken == NULL){
            return 10;
        }
        end=tokenScan(stdin, &list, mytoken);
        if (end == 0){
            printf("----------------------------------------------------------\n");
            if ((mytoken->type == Integer) || (mytoken->type == Number)){
                printf("atribut: %d\ntyp: %i\n",mytoken->data.integer, mytoken->type);
            }
            else{
                printf("atribut: %s\ntyp: %i\n",mytoken->data.string, mytoken->type);
            }

        }
        // else if (end == LEXICAL_ERROR){
        //     printf("----------------------------------------------------------\n");
        //     printf("lexikalna chyba!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        // }
    }
    //int r=0;
    //for (Token* i = list.Head; i != NULL; i = i->next){
        //printf("---------------------------------------------------\n%d. token\n",r=r+1);
        //printf("atribut: %s\ntyp: %s\n",i->att, i->type); 
    //}
    // listFree(&list);
    
    return 0;
}    