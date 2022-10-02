/*
* Nom de fichier : chaine.c
* Objectifs : Sans utiliser les bibliothèques standards ou externes :
*                                                                   - Calcul le nombre de caractère dans une chaîne de caractère
*                                                                   - Copie une chaîne dans une autre chaîne de caractère
*                                                                   - Concatène deux chaînes de caractère
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 17, 23, 27, 30, 48, 53.
*/
#include <stdio.h>

int main(){
    char phrase1[] = "Bonjour le monde !";

    // Calcul du nombre de caractères
    int i = 0;
    while (phrase1[i] != '\0'){ // Tant que on ne tombe pas sur un null donc sur la fin de la phrase, on incrémente le compteur.
        i += 1;
    }
    printf("\nNombre de caractères : %d\n", i);

    // Copie d'une chaîne de caractère
    char copie[sizeof(phrase1)]; // Création d'un char copie de la même taille que la phrase que nous voulons copier.

    for (int u=0; u<i+1;u++){
        copie[u] = '\0';
    } // Vide la chaîne de charactères "copie" en remplaçant chaque caractère par des nulls.

    for(int i = 0; i+1 < sizeof(phrase1);i++){
        copie[i] = phrase1[i]; // Parcours la phrase et la recopie dans la chaîne de caractère copie.
    }
    printf("Copie = %s\n", copie);

    // Concaténation de deux chaînes de char

    char phrase2[] = " Au revoir !"; // Création d'une nouvelle châine de caractère.
    int j = 0;
    while (phrase2[j] != '\0'){
        j += 1; // Compte la taille de phrase2.
    }
    char concat[i+j]; // Création d'un char concat de la taille de phrase1 + la taille de phrase2.
    for (int u=0; u<i+j+1;u++){
        concat[u] = '\0';
    } // Vide la chaîne de caractères "concat" en remplaçant chaque caractère par des nulls.

    i = 0;
    for(i; i+1 < sizeof(phrase1);i++){
        concat[i] = phrase1[i]; // Parcours phrase1 et la recopie dans la chaîne de caractère contact.
    }

    j = 0;
    for(j; j+1 < sizeof(phrase2);j++){
        concat[i+j] = phrase2[j]; // Parcours phrase2 et la recopie dans la chaîne de caractère contact à la suite de se qui a déjà été recopié.
    }
    printf("Concatenation = %s\n\n", concat);
    return 0;
}