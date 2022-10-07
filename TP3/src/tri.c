#include <stdio.h>
#include <stdlib.h>  // permet d'include la fonction rand, qui nous permet de créer un tableau de 100 valeurs aléatoires
#include <time.h>    // Nécessaire pour l'étape d'initialisation du générateur pseudo-aléatoire


/* Méthode de tri :
*  Le tri s'exécute via une boucle WHILE dans laquelle se situe une boucle FOR.
*  A chaque itération de la boucle FOR, celle-ci va comparer deux valeurs côte-à-côte pointées par le pointeur.
*  Si la première valeur est plus grand que la deuxième, les deux valeurs échangent leurs places.
*  Chaque itération de la boucle FOR permet d'avancer d'un cran dans le tableau.
*  Dès que deux valeurs échangent de place, un compteur s'incrémente, indiquant que le tableau n'était pas encore trié.
*  On sort de la boucle WHILE une fois qu'on est sûr que le tableau est trié (compteur = 0).
*/

int main () {
    // Initialisation du tableau
    int a[100];

    // Initialise le générateur pseudo-aléatoire
    srand(time(NULL));
            // voir fichier grand_petit.c pour explication.

    // Remplissage du tableau
    int n = 0;
    for (int i = 0 ; i < sizeof(a)/4 ; i++){
        n = rand() % 100;  
        a[i] = n;
    }

    
    // Initalisation du pointeur et du compteur d'échange
    int cpt = 1; 
    void *iptr = &a[0];

    printf("Liste non triée : \n"); // Affichage de la liste non triée
    for(int i = 0 ; i < (sizeof(a)/4) ; i++){
        printf("%d ",*((int*)iptr+i) );
        }
    printf("\n");

    while (cpt!=0){ 
        cpt = 0; // Réinitialisation du compteur
        for(int i = 0 ; i < (sizeof(a)/4)-1 ; i++){
            if (*((int*)iptr+i)>*((int*)iptr+i+1)){ // Comparaison de 2 valeurs cote à cote.
                int tempo = *((int*)iptr+i+1); // Echange de place des 2 valeurs comparées
                *((int*)iptr+i+1) = *((int*)iptr+i);
                *((int*)iptr+i) = tempo;
                cpt+=1;
            }
            }
        }

    printf("Liste triée : \n"); // Affichage de la liste triée
    for(int i = 0 ; i < (sizeof(a)/4) ; i++){
        printf("%d ",*((int*)iptr+i) );
        }
    printf("\n");

    }