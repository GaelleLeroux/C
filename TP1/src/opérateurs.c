/*
* Nom de fichier : opérateurs.c
* Objectifs : Tester toutes les opérateurs à l'aide de printf
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 14-21
*/

#include <stdio.h> 

int main () {
    int a = 16;
    int b = 3;

    printf("addition : %i \n",a+b);
    printf("soustration : %i \n",a-b);
    printf("multiplication : %i \n",a*b);
    printf("division : %f \n",(float)a/b ); // On transforme les int en float pour avoir les nombres décimaux
    printf("reste : %i \n",a%b); // Il ne fonctionne qu'avec 2 nombres entier
    printf("Négation : %i \n",!a);
    printf("Et : %i \n",a&&b);
    printf("Ou : %i \n",a||b);

    return(0);
}