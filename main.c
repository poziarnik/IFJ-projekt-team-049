
#include "Scanner.h"

int main(){
    int c = 0;
    while ( (c = fgetc(stdin)) != EOF){
        printf("%c", c);
    }
    return 0;
}    