#include <stdio.h>

int main(){
    int d = 559112;
    int m = 524296;
    if ((d&m) == m){printf("1");}
    else {printf("0");}
    printf("\n");
    return 0;
}