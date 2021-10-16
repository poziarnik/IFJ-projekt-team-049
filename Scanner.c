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

    int symbol = 0;
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
                    state = 1;
                }
                else if (symbol == '_'){
                    state = 2;
                }
                else if (symbol >= '0' && symbol <= '9')
                {
                    state = 3;
                }
                else if (symbol == '"'){
                    state = 6;
                }
                else if (symbol == '-'){
                    state = 7;
                }
                else if (symbol == '+'){
                    state = 8;
                }
                else if (symbol == '*'){
                    state = 9;
                }
                else if (symbol == '.'){
                    state = 10;
                }
                else if (symbol == '#'){
                    state = 11;
                }
                else if (symbol == '/'){
                    state = 12;
                }
                else if (symbol == '<'){
                    state = 14;
                }
                else if (symbol == '>'){
                    state = 16;
                }
                else if (symbol == '='){
                    state = 18;
                }
                else if (symbol == '~'){
                    state = 20;
                }
            case 1: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    state = 2;
                }
                else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    //TODO -- do retazca nacitat novy symbol
                }
                else{
                    ungetc(symbol, stdin);
                    if (isKeyword() == 1 ){ //porovnavam so slovom v ktorom su nahrate znaky
                        MyToken->type = "KEYWORD";
                        break;
                    }
                    else{
                        MyToken->type = "IDENTIFIKATOR";
                        break;
                    }
                }


            case 2: //TODO
                if ((symbol == '_') || (symbol >= '0' && symbol <= '9') || (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') ){
                    //ukladam do stringu        
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "IDENTIFIKATOR";
                    break;
                }
            case 3: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    //ukladam do stringu
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
                    break;
                }
            case 4: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    //pridavam do stringu
                }
                else if (symbol == 'e' || symbol == 'E'){
                    state = 5;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DESATINNY LITERAL";
                    break;
                }
            case 5: //TODO
                if (symbol >= '0' && symbol <= '9'){
                    //pridavam do stringu
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DESATINNY LITERAL";
                    break;
                }
            case 6: //TODO

            case 7: //TODO
                if (symbol == '-'){
                    //DOPISAT ASI MILION DALSICH STAVOV
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "ODCITANIE";
                    break;
                }

            case 8:
                MyToken->type = "SCITANIE";
                break;

            case 9:
                MyToken->type = "NASOBENIE";
                break;

            case 10: //TODO
                if (symbol == '.'){
                    MyToken->type = "KONKATENACIA";
                    break;
                }
                // TODO KED BUDE IBA JEDNA BODKA

            case 11:
                MyToken->type = "DLZKA";
                break;

            case 12: //TODO
                if (symbol == '/'){
                    //add to string
                    state = 13;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "DELENIE";
                    break;
                }

            case 13: 
                MyToken->type = "CELOCISELNE DELENIE";
                break; 

            case 14: //TODO
                if (symbol == '='){
                    //add to string
                    state = 15;
                }
                else{
                   ungetc(symbol, stdin);
                   MyToken->type = "LESS";
                   break; 
                }

            case 15: 
                MyToken->type = "LESS OR EQUAL";
                break;

            case 16: //TODO
                if (symbol == '='){
                    //add to string
                    state = 17;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = "GREATER";
                    break;
                }

            case 17: 
                MyToken->type = "GREATER OR EQUAL";
                break;

            case 18: //TODO
                if (symbol == '='){
                    state = 19;
                }
                //pridat co sa stane ak bude samotne =

            case 19: 
                MyToken->type = "EQUAL";
                break;

            case 20: //TODO
                if (symbol == '='){
                    state = 21;
                }
                //pridat co sa stane ak bude samotne ~
                 
            case 21: 
                MyToken->type = "APPROXIMATELY";
                break;
        }
        

        
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
