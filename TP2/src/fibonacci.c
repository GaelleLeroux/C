#include <stdio.h>

int main(){
    int u0 = 0;
    int u1 = 1;
    int un = 0;
    int cpt = 2;
    int arret = 6;
    printf("U0 = %d\n", u0);
    printf("U1 = %d\n", u1);
    for(int n = 2; n < arret; n++){
        un=u0 + u1;
        u0 = u1;
        u1 = un;
        printf("U%d = %d\n",cpt,un);
        cpt += 1;
    }
    return 0;
}