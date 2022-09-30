#include <stdio.h>

int puissance( int a, int b ) {
    int u = a;
    while( b-1 > 0 ){
        a *= u;
        b--;
    }
    return a;
}


int main() {
    int a = 3;
    int b = 3;
    int c = puissance(a,b);
    printf("%d ^ %d = %d \n",a,b,c);
    return 0;
}