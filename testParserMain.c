#include "Parser.h"
//#include "Scanner.h"
int main(){
    //printf("Meky Zbirka\n");
    TokenList *list=(TokenList*)malloc(sizeof(TokenList));
    listInit(list);
    int result=Parse(list);
    if(result==PARC_TRUE){
        printf("Meky Zbirka jubilejny koncert\n");
    }
    else if (result==PARC_FALSE){
        
        printf("%d Jozko Vajda",result);
    }
    else if (result==LEXICAL_ERROR)
    {
        printf("%d Marika Gombitova",result);
    }
    
    else if(result==10){
        printf("my global treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
        //sym_inorder(mySymtable->sym_globalTree);
        printf("\nkoniec suboru");
    }

    return 0;
}