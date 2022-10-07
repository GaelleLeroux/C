#include <stdio.h>
#include <stdlib.h>  // permet d'include la fonction rand, qui nous permet de créer un tableau de 100 valeurs aléatoires
#include <time.h>    // Nécessaire pour l'étape d'initialisation du générateur pseudo-aléatoire


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

    int num;
    printf("Veuillez entrer l'entier recherché : ");
    scanf("%d", &num); // Permet à l'utilisateur d'entrer un nombre dans le terminal

    int i = (sizeof(a)/4)/2;
    int divise = 2;
    void *iiptr = &a[i];
    int present = 0;
    int mouvement = 0;
    int u = 100;
    
    while (i!=0){
        divise*=2;
        i = (sizeof(a)/4)/(divise);
        if (num == (*((int*)iiptr+mouvement))){
            present = 1;
            break;
        }
        else if (num < (*((int*)iiptr+mouvement))){
            if (((sizeof(a)/4)/(divise)) %2==0){
                mouvement -= i;
            }
            else {
                mouvement -= (i+1);
            }
        }
        else {
            if ((((sizeof(a)/4)/(divise)) %2==0) || (i==1)){
                mouvement += i;
            }
            else {
                mouvement += (i+1);
            }
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