#include "Scanner.h"

int main(){
    int c;
    while (c!=EOF)
    {
        c = fgetc(stdin);
        printf("%c",c);
    }
    
}    