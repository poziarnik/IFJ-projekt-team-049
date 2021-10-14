#include "Scanner.h"
/*
    getToken() - stavovy automat
    Funkcia postupne cita char zo stdin a rozoduje co bude vo vystupnom tokene podla stavoveho automatu

    param Myfile - ukazatel na otvarany subor
    param MyToken - Token do ktoreho budu ulozene data
    return:
        0 - uspesne naplnenie
        1 - koniec suboru
        2 - lexikalana chyba 
*/
int getToken( FILE* Myfile, Token* MyToken){

    int c = 0;
    bool END = false;
    int state = 0;
    

    while(END != true)
    {
        c = getchar();
        
        if (c == EOF){
            END = true;
            return 1;
        }

        switch (state)
        {
            case 0:
                if(c == ' ' || c == '\n'){
                    state = 0;
                }
                else{
                    printf("%c",c);
                    state = 1;
                }
                break;
            case 1:
                if (c != ' ' && c != '\n' && c != '\t')
                {   
                    printf("%c",c);
                    state = 1;
                }
                else{
                    printf(" ");
                    END = true;
                }
                break;     
            
        }
        

        
    }
    return 0;
}
/*
    createToken()
    return:
        NULL - neuspesna alokacia
        Token* - uspesne alokovany a inicializovany token  
*/

Token* createToken(){
    Token* NewToken;
    NewToken = (Token*)malloc(sizeof(Token*));
    if (NewToken == NULL)
    {
        return NULL;
    }
   tokenInit(NewToken);
   return NewToken; 
}

/*
    param MyToken - inicializovany token 
*/
void tokenInit(Token* MyToken){
    MyToken->type = NULL;
    MyToken->att = NULL;
}