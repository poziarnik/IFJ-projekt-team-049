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
int tokenScan( FILE* Myfile, TokenList* list, Token* MyToken){

    int symbol;
    bool END = false;
    int state = 0;                      
    int sizeOfStr = 50;                 //pouzivam pre spravnu alokaciu pamate
    int CharNb = 0;
    //char* str;
    char* str=stringCreate();              //hlavny string
    //char* att=stringCreate();              //atribut
    
    
    while(END != true)
    {
        symbol = getchar();
        if (symbol == EOF){
            END = true;
            free(str);              //ak ukoncujem scan musim uvolnit posledny str a token ktore boli allocovane ale nenaplnene
            free(MyToken);
            return 1;
        }
        switch (state)
        {
            case 0:
                if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 1;                                          //identifikator
                }
                else if (symbol == '_'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 2;                                          //identifikator
                }
                else if (symbol >= '0' && symbol <= '9')
                {
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 3;                                          //intiger
                }
                else if (symbol == '"'){
                    state = 6;                                          //retazcovy literal
                }
                else if (symbol == '-'){
                    
                    state = 10;                                          //operator
                }
                else if (symbol == '+'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 16;                                          //operator
                }
                else if (symbol == '*'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 17;                                          //operator
                }
                else if (symbol == '.'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 18;                                         //operator
                }
                else if (symbol == '#'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 20;                                         //operator
                }
                else if (symbol == '/'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 21;                                         //delenie
                }
                else if (symbol == '<'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 23;                                         //operator
                }
                else if (symbol == '>'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 25;
                }
                else if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 27;
                }
                else if (symbol == '~'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 29;
                }
                else state = 0;
                break;

            case 1: 
                if (symbol >= '0' && symbol <= '9'){
                    state = 2;
                }
                else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
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

            case 2: 
                if ((symbol == '_') || (symbol >= '0' && symbol <= '9') || (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') ){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);     
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "IDENTIFIKATOR";
                    END=true;
                }
                break;

            case 3: 
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
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
                }
                break;

            case 4: 
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                }
                else if (symbol == 'e' || symbol == 'E'){
                    state = 5;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DESATINNY LITERAL";
                    END=true;
                }
                break;

            case 5:
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DESATINNY LITERAL";
                    END=true;
                }
                break;

            case 6: //TODO
                if (symbol >= 32 && symbol <= 127 && symbol != 34){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                }
                else if (symbol == '"'){
                    state = 7;
                }
                else if (symbol == '\\'){
                    state = 8;
                }
                
                
                    //treba pridat chybu
                
                break;
            
            case 7:
                MyToken->type = "RETAZCOVY LITERAL";
                END = true;
                break;
            
            case 8:
                if (symbol >= '0' && symbol <= '2'){
                    state = 9;
                }
                //else if(ak je symbol z escape sekvencie){    
                //}
                ungetc(symbol, stdin);
                break;

            case 9:
                if (symbol >= '0' && symbol <= '9'){
                    state = 31;
                }
                ungetc(symbol, stdin);
                break;

            case 31:
                //if()
                //zapisat do retazca premeneny znak
                state = 6;
                break; 

            case 10: //TODO
                if (symbol == '-'){
                    
                    state = 11;
                }
                else{
                    ungetc(symbol, stdin);
                    stringAddChar(&str,45, &sizeOfStr, &CharNb);
                    MyToken->type = "ODCITANIE";
                    END=true;
                }
                break;

            case 11:
                if (symbol == '['){
                    state = 12;
                }
                else if (symbol == '\n'){
                    state = 0;
                }
                else state = 11;
                break;

            case 12:
                if (symbol == '['){
                    state = 13;
                }
                else state = 11;
                break;
                
            case 13:
                if (symbol == ']'){
                    state = 14;
                }
                else state = 13;
                break;

            case 14:
                if (symbol == ']'){
                    state = 15;
                }
                else state = 13;
                //treba uvazovat este moznost, ze bude v komentari napriklad ]]]] ...
                break;

            case 15:
                state = 0;
                break;

            case 16:
                MyToken->type = "SCITANIE";
                END=true;
                break;

            case 17:
                MyToken->type = "NASOBENIE";
                END=true;
                break;

            case 18: //TODO
                if (symbol == '.'){
                    MyToken->type = "KONKATENACIA";
                    END=true;
                }
                break;
                // TODO KED BUDE IBA JEDNA BODKA

            case 20:
                ungetc(symbol, stdin);
                MyToken->type = "DLZKA";
                END=true;
                break;

            case 21: //TODO
                if (symbol == '/'){
                    //add to string
                    state = 22;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DELENIE";
                    END=true;
                }
                break;

            case 22: 
                ungetc(symbol, stdin);
                MyToken->type = "CELOCISELNE DELENIE";
                END=true;
                break; 

            case 23: //TODO
                if (symbol == '='){
                    //add to string
                    state = 24;
                }
                else{
                   ungetc(symbol, stdin);
                   MyToken->type = "LESS";
                   END=true;
                }
                break;

            case 24: 
                ungetc(symbol, stdin);
                MyToken->type = "LESS OR EQUAL";
                END=true;
                break;

            case 25: //TODO
                if (symbol == '='){
                    //add to string
                    state = 26;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "GREATER";
                    END=true;
                    
                }
                break;

            case 26: 
                ungetc(symbol, stdin);
                MyToken->type = "GREATER OR EQUAL";
                END=true;
                break;

            case 27: //TODO
                if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = 28;
                }
                else{
                    ungetc(symbol, stdin);
                    END=true;
                }
                //pridat co sa stane ak bude samotne =
                break;

            case 28: 
                MyToken->type = "EQUAL";
                END=true;
                break;

            case 29: //TODO
                if (symbol == '='){
                    state = 30;
                }
                //pridat co sa stane ak bude samotne ~
                break;

            case 30: 
                MyToken->type = "NOTEQUAL";
                END=true;
                break;
        }
    }
    MyToken->att=str;
    listAddToken(list, MyToken);
    return 0;
}

/*
    !!!Potrebne kontrolovat NULL navrat v MyString vonku z funkcie
    return:
        NULL - neuspesna alokacia
        Token* - uspesne alokovany a inicializovany token  
*/
Token* tokenCreate(){
    Token* NewToken;
    NewToken = (Token*)malloc(sizeof(Token));
    if (NewToken != NULL){
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

/*
    naplni token 
    param MyToken - naplneny token
    param type - typ ktory chceme do tokenu ulozit
    param att - atribut ktory chceme do tokenu ulozit
*/
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
char* stringCreate(){
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
char* stringAddChar(char** MyString, int newCharacter, int* sizeOfStr, int* charNb){
    char charValue = newCharacter ;
    if(*charNb == (*sizeOfStr)-1){
        *sizeOfStr = *sizeOfStr + 50;
        *MyString = (char*)realloc(*MyString, sizeof(char)*(*sizeOfStr));
        if (*MyString == NULL){
            return NULL;
        }
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

int isEscapeSeq(char symbol, char *string, int *stringLen){
    char sequentions[12] = "abfnrtv\\\"\'z";

    int zhoda = 0;

    for (int i = 0; i < 11; i++){
        if (symbol == sequentions[i]){
            zhoda = i;
        }
    }

    char c;

    if (zhoda != 0){
        switch (zhoda){
        case 1:
            c = 7;
            string[*(stringLen)++] = c;
            break;
        case 2:
            c = 8;
            string[*(stringLen)++] = c;
            break;
        case 3:
            c = 12;
            string[*(stringLen)++] = c;
            break;
        case 4:
            c = '\n';
            string[*(stringLen)++] = c;
            break;
        case 5:
            c = 13;
            string[*(stringLen)++] = c;
            break;
        case 6:
            c = 9;
            string[*(stringLen)++] = c;
            break;
        case 7:
            c = 11;
            string[*(stringLen)++] = c;
            break;
        case 8:
            c = '\\';
            string[*(stringLen)++] = c;
            break;
        case 9:
            c = '\"';
            string[*(stringLen)++] = c;
            break;
        case 10:
            c = '\'';
            string[*(stringLen)++] = c;
            break;
        case 11:
            //TODO SKIP WHITE SPACES \z ...
            break;
        }
    }

    return zhoda;
}

/*
    inicializujem zoznam
    zoznam je vytvoeny koli moznosti pohodlne 
    param list - inicializovany zoznam
*/
void listInit(TokenList* list){
    list->Head = NULL;
}

/*
    prida token dna koniec zoznamu
    param list - zoznam do ktoreho vkladam token
    param NewToken - pridavany token
*/
void listAddToken(TokenList* list, Token* NewToken){
    if (list->Head == NULL){
        list->Head = NewToken;
    }
    else{
        Token* i = list->Head;
        while (i->next!=NULL){
            i=i->next;
        }
        i->next = NewToken;
    }

}

/*
    uvolni vsetky tokeny ulozene v zozname
    param list - uvolnovany zoznam
*/
void listFree(TokenList* list){
    Token* tmp;
    Token* i = list->Head;
    while(i != NULL){
        tmp=i;
        i=i->next;
        free(tmp->att);
        free(tmp);
    }
}