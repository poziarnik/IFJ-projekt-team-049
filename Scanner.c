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
    int sizeOfStr = 50;                 //pouzivam pre spravnu alokaciu pamate
    int CharNb = 0;
    char* str=createStr();              //hlavny string
    char* att=createStr();              //atribut
    

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
        tokenFullup(MyToken,str,att);                       //ulozenie do tokenu
    }
    return 0;
}

/*
    !!!Potrebne kontrolovat NULL navrat v MyString vonku z funkcie
    return:
        NULL - neuspesna alokacia
        Token* - uspesne alokovany a inicializovany token  
*/
Token* createToken(){
    Token* NewToken;
    NewToken = (Token*)malloc(sizeof(Token));
    if (NewToken != NULL)
    {
        tokenInit(NewToken);
    }
    return NewToken; 
}

/*
    param MyToken - inicializovany token 
*/
void tokenInit(Token* MyToken){
    MyToken->type = NULL;
    MyToken->att = NULL;
}

void tokenFullup(Token* MyToken, char* type, char* att){
    MyToken->type = type;
    MyToken->att = att;
}

/*
    !!!Potrebne kontrolovat NULL navrat v MyString vonku z funkcie
    vytvorim string ktory budem vkladat do tokenu
    return:
        NULL - alokacia sa nepodarila
        char* - ukazatel na string
*/
char* createStr(){
    char* MyString;
    MyString=(char*)malloc(sizeof(char)*50);
    return MyString;
}

/*
    !!!Potrebne kontrolovat NULL navrat v MyString vonku z funkcie
    Prida char do stringu. Ak nie je v stringu dostatocna pamat jeho velkost sa realokuje.
    param MyString - string do ktoreho pridavam
    param newChar - zvoleny pridany charakter
    param sizeOfStr - velkost stringu po vsetky doterajsich alokaciach
    param charNb - terajsie miesto charakteru v stringu
*/
char* addToString(char** MyString, char* newCharacter, int* sizeOfStr, int* charNb){
    if(*charNb == (*sizeOfStr)-1){
        *sizeOfStr = *sizeOfStr + 50;
        *MyString = (char*)realloc(*MyString, sizeof(char)*(*sizeOfStr));
    }
    
    strcat(*MyString,newCharacter);
    *charNb = *charNb +1;
    return *MyString;
}
