/*
* Nom de fichier : tableauptr.c
* Objectifs : Pour un tableau de int et de float, on multiplie par 3 les valeurs dont l'indice est divisible par 2, à l'aide des pointeurs.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 15, 18, 19, 26, 27, 37.
*/

# include <stdio.h>

int main() {
    int ti[] = {5,700,8,9,10,11,12,13,14};
    float tf[]={3.14,5.1,6.2,7.3,8.4};

    void *tiprt = &ti[0]; // On récupère l'adresse de la première valeur du tableau.

    printf("Liste ti avant : ");
    for (int i=0;i<sizeof(ti)/4;i++){ // On divise le sizeof par 4 car un int est sur 4 octets, cela empêche le pointeur de dépasser le tableau.
        printf ("%i ",*((unsigned int*)tiprt+i)); // On transforme le pointeur en int afin de lire les 4 octets de la valeur du tableau.
    }

    printf("\n");

    void *tfprt = &tf[0];
    printf("Liste tf avant : ");
    for (int i=0;i<sizeof(tf)/4;i++){ // On divise le sizeof par 4 car un float est sur 4 octets, cela empêche le pointeur de dépasser le tableau.
        printf ("%f ",*((float*)tfprt+i)); // On transforme le pointeur en float afin de lire les 4 octets de la valeur du tableau.
    }

    printf("\n");


    //

    for (int i=0;i<sizeof(ti)/4;i++){ 
        if (i%2==0){
            *((unsigned int*)tiprt+i)*=3; // On multiplie par 3 la valeur visée par le pointeur.
        }
    }

    printf("Liste ti après : ");
    for (int i=0;i<sizeof(ti)/4;i++){
        printf ("%i ",*((unsigned int*)tiprt+i));
    }

    printf("\n");

    // 

    for (int i=0;i<sizeof(tf)/4;i++){ 
        if (i%2==0){
            *((float*)tfprt+i)*=3;
        }
    }

    printf("Liste tf après : ");


    for (int i=0;i<sizeof(tf)/4;i++){
        printf ("%f ",*((float*)tfprt+i));
    }

    printf("\n");

    return 0;
}