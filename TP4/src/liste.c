#include <stdio.h>
#include "liste.h"
#include <stdlib.h>

void insertion(struct couleur *coul, struct liste_couleurs *liste){
    struct liste_couleurs *nouveau;
    nouveau = malloc(sizeof(*nouveau));

    nouveau->couleur = coul;
    nouveau->suivant = liste->suivant;
    liste->suivant = nouveau;
}

void parcours(liste_couleurs *liste){
    struct liste_couleurs *parcour_liste = liste;
    int i = 0;
    printf("couleur 0 : %d\n",parcour_liste->couleur->rouge);
    printf("couleur 1 : %d\n",parcour_liste->suivant->couleur->rouge);
    printf("couleur 2 : %d\n",parcour_liste->suivant->suivant->couleur->rouge);
    printf("couleur 3 : %d\n",parcour_liste->suivant->suivant->suivant->couleur->rouge);
    while(parcour_liste != NULL) {
        i++;
        printf("%d : rouge : 0x%d vert : 0x%d  bleu : 0x%d alpha : 0x%d \n",i, parcour_liste->couleur->rouge,parcour_liste->couleur->vert,parcour_liste->couleur->bleu,parcour_liste->couleur->alpha);
        parcour_liste = parcour_liste->suivant;
    }
}
