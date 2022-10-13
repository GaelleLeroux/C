/*
* Nom de fichier : couleur_compteur.c
* Objectifs : Trier un tableau de couleurs aléatoires en un tableau n'ayant qu'une seule fois chaque couleur distinct,
*             ainsi que le nombre de fois où cette couleur apparaît.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 14, 44, 68-86
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    typedef struct details
    { // Création de la structure détails (R, G, B et A).
        short rouge;
        short vert;
        short bleu;
        short alpha;
    } details;

    details couleur[100]; // Définition de la taille du tableau.

    // Initialise le générateur pseudo-aléatoire
    srand(time(NULL));

    // Remplissage du tableau
    int nR = 0;
    int nV = 0;
    int nB = 0;
    int nA = 0;
    for (int i = 0; i < sizeof(couleur)/8; i++)
    {
        nR = rand() % 256;
        nV = rand() % 256;
        nB = rand() % 256;
        nA = rand() % 256;
        couleur[i].rouge = nR;
        couleur[i].vert = nV;
        couleur[i].bleu = nB;
        couleur[i].alpha = nA;
    }

    typedef struct distinct
    { // Création de la structure distinct (R, G, B et A).
        short rouge;
        short vert;
        short bleu;
        short alpha;
        short compte;
    } distinct;

    distinct diff[100]; // Définition de la taille du tableau de couleurs distinctes

    int compte_diff = 0;

    // Initialisation du tableau "distinct" (nécessaire pour bien démarrer la comparaison)
    diff[compte_diff].rouge = couleur[0].rouge;
    diff[compte_diff].bleu = couleur[0].bleu;
    diff[compte_diff].vert = couleur[0].vert;
    diff[compte_diff].alpha = couleur[0].alpha;
    diff[compte_diff].compte = 1;
    compte_diff += 1;

    int present = 0;

    // boucle de comparaison
    for (int i = 1; i < sizeof(couleur)/8 ; i++) {
        present =0;
        for (int j = 0 ; j < compte_diff ; j++){
            // Cas où la couleur est déjà présente dans le tableau
            if ((couleur[i].rouge == diff[j].rouge) && (couleur[i].bleu == diff[j].bleu) && (couleur[i].vert == diff[j].vert) && (couleur[i].alpha == diff[j].alpha)) {
                diff[j].compte += 1;
                present =1;
            }
        }
        // Cas où la couleur n'est pas présente dans le tableau (on l'ajoute)
        if (present == 0){
        diff[compte_diff].rouge = couleur[i].rouge;
        diff[compte_diff].bleu = couleur[i].bleu;
        diff[compte_diff].vert = couleur[i].vert;
        diff[compte_diff].alpha = couleur[i].alpha;
        diff[compte_diff].compte = 1;
        compte_diff += 1;
        }
    }

    for (int i = 0; i <compte_diff; i++){
        printf("r = 0x%x, v = 0x%x, b = 0x%x, a = 0x%x compte=%d \n",diff[i].rouge,diff[i].vert,diff[i].bleu,diff[i].alpha,diff[i].compte);
    }

    return 0;
}
