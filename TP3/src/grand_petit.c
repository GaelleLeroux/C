#include <stdio.h>
#include <stdlib.h>  // permet d'include la fonction rand, qui nous permet de créer un tableau de 100 valeurs aléatoires
#include <time.h>    // Nécessaire pour l'étape d'initialisation du générateur pseudo-aléatoire

int main () {
    // Initialisation du tableau
    int a[100];

    // Initialise le générateur pseudo-aléatoire
    srand(time(NULL));
            // Cette étape est obligatoire si on veut que la fonction rand() génère de nouveaux chiffres aléatoirement
            // à chaque relance du programme. Sinon, la graine de l'aléatoire reste la même à chaque compilation, et donc
            // la fonction rand() va générer la même séquence.
            // Ici, on change la graine de l'aléatoire en utilisant l'heure courante (time).

    // Remplissage du tableau
    int n = 0;
    for (int i = 0 ; i < sizeof(a)/4 ; i++){
        n = rand() % 100;   // rand() génère un nombre entre 0 et RAND_MAX définie dans la librairie. On prend le reste
                            // de sa division par 100 pour obtenir un nombre entre 0 et 99 inclu.
        a[i] = n;
    }

    // Initalisation du pointeur
    void *iptr = &a[0];

    // Boucle de comparaison
    int max = a[0];
    int min = a[0];
    for(int i = 1 ; i < sizeof(a)/4 ; i++){
        if (*((int*)iptr+i) > max){
            max = *((int*)iptr+i);        // Si le pointeur est plus grand que la valeur max enregistrée,
        }                               // celle-ci prend la valeur du pointeur.
        if (*((int*)iptr+i) < min){
            min = *((int*)iptr+i);        // Si le pointeur est plus petit que la valeur min enregistrée,
        }                               // celle-ci prend la valeur du pointeur.
    }

    printf("Nombre le plus grand : %d\n", max);
    printf("Nombre le plus petit : %d\n", min);

    return 0;
}