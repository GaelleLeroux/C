/*
* Nom de fichier : fibonacci.c
* Objectifs : Afficher la suite de Fibonacci.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 10, 11, 15, 16 21, 28.
*/

#include <stdio.h>

int fibonacci(int u0,int u1,int n,int cpt){ // Création de la fonction fibonacci.
    if (n==1) { // Condition d'arrêt.
        return 0;
    }
    else {
        printf("U%d = %d\n",cpt,u0+u1); // Affichage de Un.
        fibonacci(u1,u0+u1,n-1,cpt+1); // Appel récursif.
    }
}

int main(){
    int u0 = 0; // Initialisation des variables.
    int u1 = 1;
    int un = 0;
    int cpt = 2; // Aide à l'affichage.
    int n = 6; // Nombre d'élément affiché voulue.
    printf("U0 = %d\n", u0);
    printf("U1 = %d\n", u1);
    fibonacci(u0,u1,n,cpt); // Premier appel de la fonction.

    return 0;
}