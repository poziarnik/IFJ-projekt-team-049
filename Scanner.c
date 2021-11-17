#include "Scanner.h"
#include "error.h"

/*
    getToken() - stavovy automat
    Funkcia postupne cita char zo stdin a rozoduje co bude vo vystupnom tokene podla stavoveho automatu
    param Myfile - ukazatel na otvarany subor
    param MyToken - Token do ktoreho budu ulozene data
    
    return:
        0 - uspesne naplnenie
        10 - koniec suboru
        1 - lexikalana chyba 
*/
int tokenScan( FILE* Myfile, TokenList* list, Token* MyToken){

    int symbol;
    bool END = false;
    int state = 0;                      
    int sizeOfStr = 50;                 //pouzivam pre spravnu alokaciu pamate
    int CharNb = 0;
    char* str= stringCreate();              //hlavny string
    int escapeInt [3];
    
    
    while(END != true)
    {
        symbol = getchar();
        
        switch (state)
        {
            case Scanner_state_reading:
                if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_identifier_1;                                          //identifikator
                }
                else if (symbol == '_'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_identifier_2;                                          //identifikator
                }
                else if (symbol >= '1' && symbol <= '9')
                {
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_1;                                          //intiger
                }
                else if (symbol == '"'){
                    state = Scanner_state_string_start;                                          //retazcovy literal
                }
                else if (symbol == '-'){
                    
                    state = Scanner_state_minus;                                        
                }
                else if (symbol == '+'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Plus;
                    MyToken->data.string=str;
                    END = true;
                }
                else if (symbol == '*'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Multiplication;
                    MyToken->data.string=str;
                    END = true;                                      
                }
                else if (symbol == '.'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_concatenation;                                       
                }
                else if (symbol == '#'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Sizeof;
                    MyToken->data.string=str;
                    END = true;                                       
                }
                else if (symbol == '/'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_division;                                         //delenie
                }
                else if (symbol == '<'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_less;                                         //operator
                }
                else if (symbol == '>'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_more;
                }
                else if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_assign;
                }
                else if (symbol == '~'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_notequal;
                }
                else if (symbol == '('){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = L_bracket;
                    MyToken->data.string=str;
                    END = true;
                }
                else if (symbol == ')'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = R_bracket;
                    MyToken->data.string=str;
                    END = true;
                }
                else if (symbol == ':'){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Colon;
                    MyToken->data.string=str;
                    END = true;
                }

                else if (symbol == ','){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Comma;
                    MyToken->data.string=str;
                    END = true;
                }
                else if (symbol == EOF){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    MyToken->type = End_of_file;
                    END = true;
                    return 10;
                }
                else state = Scanner_state_reading;
                break;

            case Scanner_state_identifier_1: 
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_identifier_2;
                }
                else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || symbol == '_'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_identifier_1;
                }
                else{
                    ungetc(symbol, stdin);
                    if (isKeyword(str) == 1 ){ //porovnavam so slovom v ktorom su nahrate znaky
                        MyToken->type = 1;
                        MyToken->data.string = str;
                        END=true;
                    }
                    else{
                        MyToken->type = 0;
                        MyToken->data.string = str;
                        END=true;
                    }
                }
                //state=1;
                break;

            case Scanner_state_identifier_2: 
                if ((symbol == '_') || (symbol >= '0' && symbol <= '9') || (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') ){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);     
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = 0;
                    MyToken->data.string = str;
                    END=true;
                }
                break;

            case Scanner_state_number_1: 
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_1;
                }
                else if (symbol == '.'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_5;
                }
                else if (symbol == 'e' || symbol == 'E'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_3;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Integer;
                    MyToken->data.integer = atoi(str);
                    END=true;
                }
                break;

            case Scanner_state_number_2: 
                if (symbol >= '0' && symbol <= '9'){ 
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);                   
                    state = Scanner_state_number_2;
                }
                else if (symbol == 'e' || symbol == 'E'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_3;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Number;
                    MyToken->data.number = strtod(str, NULL);
                    END=true; 
                }
                break;

            case Scanner_state_number_3:
                if (symbol >= '1' && symbol <= '9'){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_4;
                }
                else if (symbol == '0'){
                    state = Scanner_state_number_3;
                }
                else if ((symbol == '+' ) || (symbol == '-')){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_4;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Number;
                    MyToken->data.number = strtod(str, NULL);
                    END=true;
                }
                break;

             case Scanner_state_number_4:
                 if ((symbol >= '0' && symbol <= '9')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_4;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Number;
                    MyToken->data.number = strtod(str, NULL);
                    END = true;
                }
                break;

            case Scanner_state_number_5:
                if ((symbol >= '0' && symbol <= '9')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_2;
                }
                else{
                    return LEXICAL_ERROR;
                }
                
                break;
                
            case Scanner_state_string_start: //TODO
                if (symbol >= 32 && symbol <= 127 && symbol != 34 && symbol != 92){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                }
                else if (symbol == '"'){
                    state = Scanner_state_string_end;
                }
                else if (symbol == '\\'){
                    state = Scanner_state_string_1;
                }
                else{
                    return LEXICAL_ERROR;
                }
                break;
            
            case Scanner_state_string_end:
                MyToken->type = String;
                MyToken->data.string = str;
                END = true;
                break;
            
            case Scanner_state_string_1:
                if (symbol >= '0' && symbol <= '2'){
                    escapeInt[0]=symbol;
                    state = Scanner_state_string_2;
                }
                else{
                    int isESC=isEscapeSeq(symbol);
                    if (isESC != -1){
                         stringAddChar(&str,isESC, &sizeOfStr, &CharNb);
                    }
                    else{
                        ungetc(symbol,stdin);
                    }   
                    state = Scanner_state_string_start;
                }
                break;

            case Scanner_state_string_2:
                if (symbol >= '0' && symbol <= '9'){
                    escapeInt[1]=symbol;
                    state = Scanner_state_string_3;
                }
                else{
                    return LEXICAL_ERROR;
                }
                
                break;

            case Scanner_state_string_3:
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str,(escapeInt[0]-48)*100+(escapeInt[1]-48)*10+(symbol-48), &sizeOfStr, &CharNb);
                }
                else{
                    state = Scanner_state_string_start;
                }
                break; 

            case Scanner_state_minus: 
                if (symbol == '-'){
                    state = Scanner_state_comment_start;
                }
                else{
                    ungetc(symbol, stdin);
                    stringAddChar(&str,45, &sizeOfStr, &CharNb);
                    MyToken->type = Minus;
                    MyToken->data.string = str;
                    END=true;
                }
                break;

            case Scanner_state_comment_start:
                if (symbol == '['){
                    state = Scanner_state_comment_block;
                }
                else if (symbol == '\n'){
                    state = Scanner_state_reading;
                }
                else{ 
                    state = Scanner_state_comment_start;
                }
                break;

            case Scanner_state_comment_block:
                if (symbol == '['){
                    state = Scanner_state_comment_block_start;
                }
                else{ 
                    state = Scanner_state_comment_start;
                }
                break;
                
            case Scanner_state_comment_block_start:
                if (symbol == ']'){
                    state = Scanner_state_comment_block_end1;
                }
                else{ 
                    state = Scanner_state_comment_block_start;
                }
                break;

            case Scanner_state_comment_block_end1:
                if (symbol == ']'){
                    state = Scanner_state_reading;
                }
                else{
                    state = Scanner_state_comment_block_start;
                }
                break;

            case Scanner_state_concatenation: //TODO
                if (symbol == '.'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Concatenation;
                    MyToken->data.string = str;
                    END=true;
                }
                else{
                    ungetc(symbol, stdin);
                    return LEXICAL_ERROR;
                }
                break;

            case Scanner_state_division:
                if (symbol == '/'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Division_integer;
                    MyToken->data.string = str;
                    END=true;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Division;
                    MyToken->data.string = str;
                    END=true;
                }
                break;

            case Scanner_state_less: 
                if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Less_equal;
                    MyToken->data.string = str;
                    END = true;
                }
                else{
                   ungetc(symbol, stdin);
                   MyToken->type = Less;
                   MyToken->data.string = str;
                   END=true;
                }
                break;

            case Scanner_state_more: 
                if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = More_equal;
                    MyToken->data.string = str;
                    END=true;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = More;
                    MyToken->data.string = str;
                    END=true; 
                }
                break;

            case Scanner_state_assign: //TODO
                if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Is_equal;
                    MyToken->data.string = str;
                    END = true;
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Assign;
                    END=true;
                }
                break;

            case Scanner_state_notequal:
                if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Not_equal;
                    MyToken->data.string = str;
                    END=true;
                }
                else{
                    ungetc(symbol,stdin);
                    return LEXICAL_ERROR;
                }
                break;
        }
    }
    // listAddToken(list, MyToken);
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
    // else{
    //     return INTERNAL_ERROR;
    // }
    return NewToken; 
}

/*
    param MyToken - inicializovany token 
*/
void tokenInit(Token* MyToken){
    // MyToken->type = NULL;
    MyToken->data.string = NULL;
    MyToken->data.integer = 0;
    MyToken->data.number = 0;
}

/*
    naplni token 
    param MyToken - naplneny token
    param type - typ ktory chceme do tokenu ulozit
    param att - atribut ktory chceme do tokenu ulozit
*/
// void tokenFullup(Token* MyToken, Token_type type, char* att){
//     MyToken->type = type;
//     MyToken->data.string = att;
// }

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
    return - cislo znaku v tabulke
    return - -1 ak nie je sucastou tabulky
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

int isEscapeSeq(int symbol){
    char sequentions[12] = "abfnrtv\\\"\'z";

    int zhoda = 0;

    for (int i = 0; i < 11; i++){
        if (symbol == sequentions[i]){
            zhoda = i;
        }
    }

    int c=-1;

    if (zhoda != 0){
        switch (zhoda){
        case 1:
            c = 7;
            break;
        case 2:
            c = 8;
            break;
        case 3:
            c = 12;
            break;
        case 4:
            c = 10;
            break;
        case 5:
            c = 13;
            break;
        case 6:
            c = 9;
            break;
        case 7:
            c = 11;
            break;
        case 8:
            c = 92;
            break;
        case 9:
            c = 34;
            break;
        case 10:
            c = 39;
            break;
        case 11:
            //TODO SKIP WHITE SPACES \z ...
            break;
        }
    }

    return c;
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
        if ((tmp->type != Number) || (tmp->type != Integer) )
        {
            free(tmp->data.string);
        }
        
        
        free(tmp);
    }
}



/*lexikalne chyby
        1. e- / e+  bez nasledujuceho cisla spusti chybu napr 123e-A      
*/

