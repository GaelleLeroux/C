/*
* Nom de fichier : boucles.c
* Objectifs : Afficher un triangle rectangle dans la console à l'aide d'une boucle
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 13, 14, 17, 27, 35, 36, 39, 41, 51
*/

#include <stdio.h> 

int main () {
    int compteur = 6; // taille d'un côté du triangle

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