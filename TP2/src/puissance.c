#include <stdio.h>

int puissance( int a, int b ) {
    int u = a;
    while( b > 0 ){
        a *= u;
        b--;
    }
}


int main() {
    int a = 2;
    int b = 3;
    int c = puissance(a,b);
    printf("%d ^ %d = %d \n",a,b,c);
    return 0;
}