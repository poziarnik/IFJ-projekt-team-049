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

    int symbol;
    bool END = false;
    int state = 0;                      
    int sizeOfStr = 50;                 //pouzivam pre spravnu alokaciu pamate
    int CharNb = 0;
    char* str=createStr();              //hlavny string
    char* att=createStr();              //atribut
    
    
    while(END != true)
    {
        symbol = getchar();
        if (symbol == EOF){
            END = true;
            return 1;
        }
        switch (state)
        {
            case 0:
                if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 1;                                          //identifikator
                }
                else if (symbol == '_'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 2;                                          //identifikator
                }
                else if (symbol >= '0' && symbol <= '9')
                {
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 3;                                          //intiger
                }
                else if (symbol == '"'){
                    state = 6;                                          //retazcovy literal
                }
                else if (symbol == '-'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 7;                                          //operator
                }
                else if (symbol == '+'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 8;                                          //operator
                }
                else if (symbol == '*'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 9;                                          //operator
                }
                else if (symbol == '.'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 10;                                         //operator
                }
                else if (symbol == '#'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 11;                                         //operator
                }
                else if (symbol == '/'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 12;                                         //delenie
                }
                else if (symbol == '<'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 14;                                         //operator
                }
                else if (symbol == '>'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 16;
                }
                else if (symbol == '='){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 18;
                }
                else if (symbol == '~'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                    state = 20;
                } 
                break;
            case 1: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    state = 2;
                }
                else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                }
                else{
                    ungetc(symbol, stdin);
                    if (isKeyword(str) == 1 ){ //porovnavam so slovom v ktorom su nahrate znaky
                        MyToken->type = "KEYWORD";
                        END=true;
                    }
                    else{
                        MyToken->type = "IDENTIFIKATOR";
                        END=true;
                    }
                }
                //state=1;
                break;

            case 2: //TODO
                if ((symbol == '_') || (symbol >= '0' && symbol <= '9') || (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') ){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);     
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "IDENTIFIKATOR";
                    END=true;
                    break;
                }
            case 3: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                }
                else if (symbol == '.'){
                    state = 4;
                }
                else if (symbol == 'e' || symbol == 'E'){
                    state = 5;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "CELE CISLO";
                    END=true;
                    break;
                }
            case 4: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                }
                else if (symbol == 'e' || symbol == 'E'){
                    state = 5;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DESATINNY LITERAL";
                    END=true;
                    break;
                }
            case 5: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    addToString(&str,symbol, &sizeOfStr, &CharNb);
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DESATINNY LITERAL";
                    END=true;
                    break;
                }
            case 6: //TODO
                ungetc(symbol, stdin);
                END=true;
                break;
            case 7: //TODO
                if (symbol == '-'){
                    //DOPISAT ASI MILION DALSICH STAVOV
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "ODCITANIE";
                    END=true;
                }
                break;
            case 8:
                MyToken->type = "SCITANIE";
                END=true;
                break;

            case 9:
                MyToken->type = "NASOBENIE";
                END=true;
                break;

            case 10: //TODO
                if (symbol == '.'){
                    MyToken->type = "KONKATENACIA";
                    END=true;
                }
                break;
                // TODO KED BUDE IBA JEDNA BODKA

            case 11:
                ungetc(symbol, stdin);
                MyToken->type = "DLZKA";
                END=true;
                break;

            case 12: //TODO
                if (symbol == '/'){
                    //add to string
                    state = 13;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DELENIE";
                    END=true;
                }
                break;
            case 13: 
                ungetc(symbol, stdin);
                MyToken->type = "CELOCISELNE DELENIE";
                END=true;
                break; 

            case 14: //TODO
                if (symbol == '='){
                    //add to string
                    state = 15;
                }
                else{
                   ungetc(symbol, stdin);
                   MyToken->type = "LESS";
                   END=true;
                }
                break;
            case 15: 
                ungetc(symbol, stdin);
                MyToken->type = "LESS OR EQUAL";
                END=true;
                break;

            case 16: //TODO
                if (symbol == '='){
                    //add to string
                    state = 17;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "GREATER";
                    END=true;
                    
                }
                break;
            case 17: 
                ungetc(symbol, stdin);
                MyToken->type = "GREATER OR EQUAL";
                END=true;
                break;

            case 18: //TODO
                if (symbol == '='){
                    state = 19;
                }
                //pridat co sa stane ak bude samotne =
                break;
            case 19: 
                ungetc(symbol, stdin);
                MyToken->type = "EQUAL";
                END=true;
                break;

            case 20: //TODO
                if (symbol == '='){
                    state = 21;
                }
                //pridat co sa stane ak bude samotne ~
                break;
            case 21: 
                MyToken->type = "NOTEQUAL";
                END=true;
                break;
        }
        

        
    }
    printf("%s\n",str);
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
char* addToString(char** MyString, int newCharacter, int* sizeOfStr, int* charNb){
    char charValue = newCharacter ;
    if(*charNb == (*sizeOfStr)-1){
        *sizeOfStr = *sizeOfStr + 50;
        *MyString = (char*)realloc(*MyString, sizeof(char)*(*sizeOfStr));
    }
    
    strcat(*MyString,&charValue);
    *charNb = *charNb +1;
    return *MyString;
}
/* 
    Tabulka klucovych slov
    skontoluje ci sa predany string nachadza v tabulke
    param word - kontrolovany string 
*/
int isKeyword(char *word){
    char keyword[15][10]={
        "do","else","end","function","global","if","integer",
        "local","nil","number","require","return","string",
        "then","while" 
    } ;

    int zhoda = 0;

    for (int i = 0; i < 15; i++){
        if (strcmp(word, keyword[i]) == 0){
            zhoda = 1;
        }
    }

    return zhoda;

}
