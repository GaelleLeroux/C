#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
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

    int num;
    printf("Veuillez entrer l'entier recherché : ");
    scanf("%d", &num); // Permet à l'utilisateur d'entrer un nombre dans le terminal

    // Initialisation du pointeur
    void *iptr = &a[0];

    int present = 0;

    for (int i = 0 ; i < sizeof(a)/4 ; i++){
        if (*((int*)iptr+i) == num){
            present = 1;
            break;  // On évite de traverser le tableau pour rien
        }
    }

    if (present == 1){
        printf("Entier présent.\n");
    }
    else{
        printf("Entier non présent.\n");
    }
    return 0;
}