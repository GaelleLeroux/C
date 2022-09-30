#include <stdio.h> 

int main () {
    int compteur = 6;

    for ( int a = 0; a < compteur-1; a++){
        if (a==0){
            printf("*");
        }
        if (a>0) {
            printf("*");
            for (int b=0;b<a-1;b++){
                printf("#");
            }
            printf("*");
        }
        printf("\n");

    }
    for (int a = 0; a <compteur;a++){
        printf("*");
    }

    printf(" \n Version while \n");

    int a = 0;
    int compteur2 = compteur;
    while (compteur2>1){
        if (a==0){
                printf("*");
            }
            if (a>0) {
                printf("*");
                for (int b=0;b<a-1;b++){
                    printf("#");
                }
                printf("*");
            }
            printf("\n");
        compteur2-=1;
        a+=1;
    }

    for (int a = 0; a <compteur;a++){
        printf("*");
    }
}