#include <stdio.h>

int puissance( int a, int b, int p ) {
    b-=1;
    if (b==0){
        return a;
    }
    else{
        a*=p;
        puissance(a,b,p);
    }
}


int main() {
    int a = 4;
    int b = 4;
    int c = puissance(a,b,a);
    printf("%d ^ %d = %d \n",a,b,c);
    return 0;
}