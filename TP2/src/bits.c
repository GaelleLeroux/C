/*
* Nom de fichier : bits.c
* Objectifs : Vérifier si les 4èmes et 20èmes bits de gauche sont à 1.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 12, 13.
*/

#include <stdio.h>

int main(){
    int d = 559112;
    int m = 524296; // Masque correspondant en binaire à 10000000000000001000.
    if ((d&m) == m){printf("1");} // Application du masque et affichage si réussite.
    else {printf("0");}
    printf("\n");
    return 0;
}