/*
* Nom de fichier : cercle.c
* Objectifs : Réaliser des opérations dans la fonction printf.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 12, 13
*/

#include <stdio.h> 

int main () {
    float rayon = 5;
    printf("L'aire du cercle est : %f \n",3.14*rayon*rayon); // Calcul de l'aire selon l'équation pi*r^2
    printf("Le périmètre du cercle est : %f \n",2*3.14*rayon); // Calcul du périmètre selon l'équation 2*pi*r
    return(0);
}