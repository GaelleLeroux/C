/*
* Nom de fichier : recherche_dichotomique.c
* Objectifs : - Chercher un nombre dans une liste via une recherche dichotomique.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 15, 22, 37, 38, 53, 59, 6, 63, 65, 67, 71, 74, 75
*/

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
    int mouvement = 0; // permettra de savoir si la liste a été coupée à gauche ou à droite et donc de se replacer au bon endroit pour la comparaison
    int u = 100;
    
    while (i!=0){ // Tant que on peut diviser la liste donc que nous n'avons pas encore finit rechercher le nombre
        divise*=2; // On la redivise par 2
        i = (sizeof(a)/4)/(divise);
        if (num == (*((int*)iiptr+mouvement))){ // On compare le numéro entrer avec le milieux de la liste restante
            present = 1; 
            break; // On sort si l enombre a éé=té trouvé
        }
        else if (num < (*((int*)iiptr+mouvement))){ // Vérifie si l enmbre est au dessus ou au dessous
            if (((sizeof(a)/4)/(divise)) %2==0){
                mouvement -= i; // Si la liste est paire on enlève la moitié de la liste
            }
            else {
                mouvement -= (i+1); // Si elle est impaire on enlève la moitié+1 de la liste
                                    // Cela nous permet de bien englober les bords
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