/*
* Nom de fichier : sizeof.c
* Objectifs : Afficher dans le terminal la taille en octet de tous les types de variables
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 12-24
*/

#include <stdio.h> 
#include <limits.h>

int main () {
    printf("sizeof(char) : %lu \n",sizeof(char));
    printf("sizeof(char *) : %lu \n",sizeof(char *));
    printf("sizeof(char **) : %lu \n",sizeof(char **));
    printf("sizeof(char ***)) : %lu \n",sizeof(char ***));

    printf("sizeof(int) : %lu \n",sizeof(int));
    printf("sizeof(int *) : %lu \n",sizeof(int *));
    printf("sizeof(int **) : %lu \n",sizeof(int **));

    printf("sizeof(float) : %lu \n",sizeof(float));
    printf("sizeof(float *) : %lu \n",sizeof(float *));
    printf("sizeof(float **) : %lu \n",sizeof(float **));
    printf("sizeof(float ***) : %lu \n",sizeof(float ***));
    return(0);
}