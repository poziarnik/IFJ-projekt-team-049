#include "Scanner.h"

/*
    zatial len skusanie
    getToken vrati slovo oddelene medzerou alebo koncom riadku
    make primitive - preklad bez varovani
    make advanced - preklad s varovaniami
    spustenie - ./test<main.c 
              - cita so stdin tak bz malo ist spusti z hocijakym suborom napr <Scanner.c <Scanner.h whatever
*/
int main(){

    
    for (int i = 0; i < 100; i++)
    {
        Token* mytoken = createToken();
        if(mytoken == NULL){
            return 1;
        }
        getToken(stdin, mytoken);
    }
    
    
    
    //Token* MyToken=createToken();
    

    //getToken(stdin, 5);
    return 0;
}    