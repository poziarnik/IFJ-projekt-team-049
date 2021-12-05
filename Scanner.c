
#include "Scanner.h"
#include "error.h"
#include <string.h>


/*
    tokenScan() - stavovy automat
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
    char* str= stringCreate();           //hlavny string

    if (str == NULL) return INTERNAL_ERROR;
    
    int escapeInt [3];
    int finalnumber;
    
    while(END != true)
    {
        symbol = getchar();
        
        switch (state)
        {
            //Stav citania, token sa nezapisuje
            case Scanner_state_reading:
                //ak slovo zacina malym alebo velkym pismenom
                if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb); //pridavam do retazca
                    state = Scanner_state_identifier_1;   //menim stav na identifikator    
                }

                //ak prichadza znak podtrzitka
                else if (symbol == '_'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);  //pridavam do retazca
                    state = Scanner_state_identifier_2;  //identifikator
                }

                //ak prichadzaju cislice od 0 po 9
                else if (symbol >= '0' && symbol <= '9')
                {
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb); //pridavam do retazca
                    state = Scanner_state_number_1;   //skacem na stav number_1
                }

                //ak prichadzaju dvojite uvodzovky
                else if (symbol == '"'){      //nezapisujem do retazca
                    state = Scanner_state_string_start;    //retazcovy literal
                }

                //ak prichadza znak minus, moze to byt bud znamienko, alebo komentar
                else if (symbol == '-'){
                    state = Scanner_state_minus;      //prechadzam na stav minus                                  
                }

                //symbol plus 
                else if (symbol == '+'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Plus;  //nastavim typ tokenu na plus
                    MyToken->data.string=str;   //do tokenu pridam znak plus
                    END = true;    //plus je zaroven aj koncovy stav
                }

                //symbol krat
                else if (symbol == '*'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Multiplication; //nastavujem typ
                    MyToken->data.string=str;   //pridavam do retazca v tokene
                    END = true;    //je zaroven aj koncovy stav                           
                }

                // symbol bodka
                else if (symbol == '.'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);  //pridam do retazca
                    state = Scanner_state_concatenation;    //prechadzam na stav konkatenacia                            
                }

                //symbol hashtag
                else if (symbol == '#'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb); //pridam do retazca
                    MyToken->type = Sizeof;  //typ tokenu nastavim na sizeof
                    MyToken->data.string=str; //do tokenu ulozim znak
                    END = true;   // je koncovy stav               
                }

                //symbol lomeno
                else if (symbol == '/'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb); //pridam do retazca
                    state = Scanner_state_division;      //delenie
                }

                //symbol mensi
                else if (symbol == '<'){ 
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb); //pridavam do retazca
                    state = Scanner_state_less;    //stav --> less
                }

                //symbol vacsi
                else if (symbol == '>'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb); 
                    state = Scanner_state_more; //stav --> more
                }

                //symbol rovna sa
                else if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_assign; //stav --> assign
                }

                //symbol ~
                else if (symbol == '~'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_notequal; //stav --> notequal
                }

                //symbol lava zatvorka
                else if (symbol == '('){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = L_bracket; //nastavim typ tokenu
                    MyToken->data.string=str;   //pridam do retazca
                    END = true; //je zaroven koncovy stav
                }

                //symbol prava zatvorka
                else if (symbol == ')'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = R_bracket; //nastavim typ tokenu
                    MyToken->data.string=str;   //pridavam do retazca
                    END = true; //koncovy stav
                }

                //symbol dvojbodka
                else if (symbol == ':'){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Colon; // nastavujem typ tokenu
                    MyToken->data.string=str; //pridavam do retazca
                    END = true; //koncovy stav
                }

                //symbol ciarka
                else if (symbol == ','){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Comma; //typ --> Comma
                    MyToken->data.string=str; // retazec <--
                    END = true; // stav --> end
                }

                //symbol konca suboru
                else if (symbol == EOF){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    MyToken->type = End_of_file; //typ --> End_of_file
                    END = true; //koncovy stav
                    return 10;
                }

                //ak prichadzaju znaky 
                else if(isspace(symbol)!=0) state = Scanner_state_reading; // ak je biely znak ostavam na stave reading
                else return LEXICAL_ERROR; //ak pride insi znak vraciam LEXIKALNU chybu
                break;

            //Identifikatory a klucove slova
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
                    if (isKeyword(str) == 1 ){ //retazec porovnam s klucovymi slovami
                        MyToken->type = 1; // typ -> keyword
                        MyToken->data.string = str; //ulozim retazec
                        END=true; //koncovy stav
                    }
                    else{
                        MyToken->type = 0; //typ --> identifikator
                        MyToken->data.string = str; //ulozim retazec
                        END=true; //koncovy stav
                    }
                }
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

            //cisla
            case Scanner_state_number_1: 
                if (symbol >= '0' && symbol <= '9'){  
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_1; //state --> state
                }
                else if (symbol == '.'){  
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_5; //state -> number_5
                }
                else if (symbol == 'e' || symbol == 'E'){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_3; //state --> number_3
                }
                else{  
                    ungetc(symbol, stdin);
                    MyToken->type = Integer; //type --> Integer
                    MyToken->data.integer = atoi(str); // ukladam hodnotu
                    END=true; // konecny stav
                }
                break;

            case Scanner_state_number_2: 
                if (symbol >= '0' && symbol <= '9'){ 
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);                   
                    state = Scanner_state_number_2; //state --> state
                }
                else if (symbol == 'e' || symbol == 'E'){  //ak pride E alebo e
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_3; //state --> number_3
                }
                else{ 
                    ungetc(symbol, stdin); //vraciam znak
                    MyToken->type = Number; //type --> Number
                    MyToken->data.number = strtod(str, NULL);
                    END=true;  //koncovy stav
                }
                break;

            case Scanner_state_number_3: // moze prist iba cislo, alebo + a -
                if (symbol >= '0' && symbol <= '9'){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_4; //state --> number_4
                }
                else if ((symbol == '+' ) || (symbol == '-')){
                    stringAddChar(&str, symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_6; //state --> number_6
                }
                else{
                    return LEXICAL_ERROR; //ak nepride ani cislo
                }
                break;

             case Scanner_state_number_4:
                 if ((symbol >= '0' && symbol <= '9')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_4; //state --> state
                }
                else{
                    ungetc(symbol, stdin);
                    MyToken->type = Number; //type --> Number
                    MyToken->data.number = strtod(str, NULL);
                    END = true; //koncovy stav
                }
                break;

            case Scanner_state_number_5: 
                if ((symbol >= '0' && symbol <= '9')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_2; //state --> number_2
                }
                else{
                    return LEXICAL_ERROR; //ak je bodka a za nou nejde cislo
                }
                
                break;
            
            case Scanner_state_number_6:
                if ((symbol >= '0' && symbol <= '9')){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    state = Scanner_state_number_4; //state --> number_4
                }
                else{
                    return LEXICAL_ERROR; //ak je iba 'e'/'E' a nepride cislo
                }
                break;

            //Stringy
            case Scanner_state_string_start: 
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
                ungetc(symbol,stdin);
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
                        return LEXICAL_ERROR;
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
                    
                    finalnumber = (escapeInt[0]-48)*100+(escapeInt[1]-48)*10+(symbol-48);
                    
                    if (finalnumber < 001 || finalnumber >255){
                        return LEXICAL_ERROR;
                    }
    
                    stringAddChar(&str,(escapeInt[0]-48)*100+(escapeInt[1]-48)*10+(symbol-48), &sizeOfStr, &CharNb);
                    state = Scanner_state_string_start;
                }
                else{
                    return LEXICAL_ERROR;
                }
                break; 

            //komentare
            case Scanner_state_minus: 
                if (symbol == '-'){ 
                    state = Scanner_state_comment_start; //state --> comment_start
                }
                else{ 
                    ungetc(symbol, stdin); //vraciam znak
                    stringAddChar(&str,45, &sizeOfStr, &CharNb);
                    MyToken->type = Minus; //type --> Minus (-)
                    MyToken->data.string = str; 
                    END=true; //koncovy stav
                }
                break;

            case Scanner_state_comment_start:
                if (symbol == '['){  
                    state = Scanner_state_comment_block; //state --> comment_block
                }
                else if (symbol == '\n' || symbol == EOF){ 
                    ungetc(symbol, stdin);  //vraciam znak
                    state = Scanner_state_reading;  // state --> reading
                }
                else{  //vsetko ostatne
                    state = Scanner_state_comment_start; //state --> state
                }
                break;

            case Scanner_state_comment_block:
                if (symbol == '['){  
                    state = Scanner_state_comment_block_start; //state --> comment_block_start
                }
                else if (symbol == '\n' || symbol == EOF){
                    return LEXICAL_ERROR;
                }
                else{  
                    state = Scanner_state_comment_start; //state --> comment_start
                }
                break;

            //blokove komentare    
            case Scanner_state_comment_block_start:
                if (symbol == ']'){ //ak prisiel znak ']'
                    state = Scanner_state_comment_block_end1; //state -->comment_block_end1
                }
                else if (symbol == '\n' || symbol == EOF){
                    return LEXICAL_ERROR;
                }
                else{  
                    state = Scanner_state_comment_block_start; //state --> state
                }
                break;

            case Scanner_state_comment_block_end1:
                if (symbol == ']'){ //ak prisiel dalsi znak ']', je to koniec blokoveho komentara
                    state = Scanner_state_reading; // state --> state_reading
                }
                else{ //blokovy koment konci iba dvoma znakmy ']'
                    state = Scanner_state_comment_block_start; //state --> comment_block_start
                }
                break;

            //Konkatenacia
            case Scanner_state_concatenation: 
                if (symbol == '.'){ //ak su dva znaky '.'
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Concatenation; //type -->Concatenation
                    MyToken->data.string = str;
                    END=true; //koncovy stav
                }
                else{ 
                    ungetc(symbol, stdin); //vraciam znak
                    return LEXICAL_ERROR; // podla zadania nemoze byt samotna bodka
                }
                break;

            //Delenie
            case Scanner_state_division:
                if (symbol == '/'){ //ak su dva znaky '/'
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Division_integer; //type --> Division_integer
                    MyToken->data.string = str;
                    END=true; //koncovy stav
                }
                else{
                    ungetc(symbol, stdin); //vraciam znak
                    MyToken->type = Division; // type -->Division
                    MyToken->data.string = str;
                    END=true; //koncovy stav
                }
                break;

            //Relacne operatory
            case Scanner_state_less: 
                if (symbol == '='){
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Less_equal; //type --> Less_equal (<=)
                    MyToken->data.string = str;
                    END = true; //konecny stav
                }
                else{
                   ungetc(symbol, stdin);
                   MyToken->type = Less; //type --> Less (<)
                   MyToken->data.string = str;
                   END=true; //konecny stav
                }
                break;

            case Scanner_state_more: 
                if (symbol == '='){ //ak pride po znaku > znak =
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = More_equal; //type --> More_equal (>=)
                    MyToken->data.string = str;
                    END=true; //koncovy stav
                }
                else{ 
                    ungetc(symbol, stdin); //ak pride nieco ine vraciam znak
                    MyToken->type = More; //type --> More (>)
                    MyToken->data.string = str;
                    END=true; //koncovy stav
                }
                break;

            case Scanner_state_assign:
                if (symbol == '='){ //ak su 2 rovna sa
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Is_equal; //type --> Is_equal (==)
                    MyToken->data.string = str; 
                    END = true; //koncovy stav
                }
                else{
                    ungetc(symbol, stdin); //ak je iba jedno rovna sa tak vraciam znak
                    MyToken->type = Assign; //type --> Assign (=)
                    MyToken->data.string = str; 
                    END=true;   //koncovy stav
                }
                break;

            case Scanner_state_notequal:
                if (symbol == '='){ 
                    stringAddChar(&str,symbol, &sizeOfStr, &CharNb);
                    MyToken->type = Not_equal; //type --> Not_equal (~=)
                    MyToken->data.string = str;
                    END=true; //koncovy stav
                }
                else{   // ak je iba znak ~
                    ungetc(symbol,stdin); 
                    return LEXICAL_ERROR; //Lexikalna chyba
                }
                break;
        }
    }
    //listAddToken(list, MyToken);
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
    if (MyString == NULL){
        return NULL;
    }
    
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
    char charValue = newCharacter;
    if(*charNb == (*sizeOfStr)-1){
        *sizeOfStr = *sizeOfStr + 50;
        *MyString = (char*)realloc(*MyString, sizeof(char)*(*sizeOfStr));
        if (*MyString == NULL) return NULL;
    }
    
    strncat(*MyString,&charValue, 1);
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

    int zhoda = -1;

    for (int i = 0; i < 11; i++){
        if (symbol == sequentions[i]){
            zhoda = i;
        }
    }

    int c=-1;

    if (zhoda != -1){
        switch (zhoda){
        case 0:
            c = 7;
            break;
        case 1:
            c = 8;
            break;
        case 2:
            c = 12;
            break;
        case 3:
            c = 10;
            break;
        case 4:
            c = 13;
            break;
        case 5:
            c = 9;
            break;
        case 6:
            c = 11;
            break;
        case 7:
            c = 92;
            break;
        case 8:
            c = 34;
            break;
        case 9:
            c = 39;
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


