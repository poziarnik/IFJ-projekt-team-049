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

    Token* mytoken;
    getToken(stdin, mytoken);

    if ((createToken(mytoken)) == NULL){
        
        return 1;
    }


    
    getToken(stdin, mytoken);
    getToken(stdin, mytoken);
    getToken(stdin, mytoken);
    getToken(stdin, mytoken);
    getToken(stdin, mytoken);
    getToken(stdin, mytoken);
    getToken(stdin, mytoken);
    
    

    //getToken(stdin, 5);
    return 0;
}    