/*
* Nom de fichier : puissance.c
* Objectifs : Calculer la puissance de a^b.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 12, 17, 23, 25, 26.
*/

#include <stdio.h>

int puissance( int a, int b, int p ) {
    b-=1;
    if (b==0){ // Condition d'arrêt
        return a;
    }
    else{
        a*=p;
        puissance(a,b,p); // Appel récursif.
    }
}


int main() {
    int a = 4; // Initialisation des variables.
    int b = 4;
    int c = puissance(a,b,a); // Premier appel de la fonction.
    printf("%d ^ %d = %d \n",a,b,c); // Affichage du résultat.
    return 0;
}