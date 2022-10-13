/*
* Nom de fichier : binaire.c
* Objectifs : Afficher un entier en base 10 sous forme binaire.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 15-19
*/

#include <stdio.h> 

int main () {
    unsigned int a = 65538;

    unsigned long int b=65536; // Il s'agit du masque 10000000000000000 (16 zéros)
    int p = 17; // permet d'afficher les décimaux bit à bit jusqu'a 2^17 - 1 = 131 071, p est l'indice du bit étudié.
    while (p!=0){
        if ((b&a)==b){printf("1");} // on applique un masque pour isoler chaque bit du nombre étudié.
        else {printf("0");} // Si il vaut 1 on affiche 1 sinon 0.
        p-=1; // passe au bit suivant.
        b=b>>1; // Décale à droite l'unique bit à l'état haut du masque.
    }

    printf("\n");
    return 0;
}