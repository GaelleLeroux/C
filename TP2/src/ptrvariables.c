/*
* Nom de fichier : ptrvariables.c
* Objectifs : Afficher les valeurs en héxadécimal des différents types en utilisant leur adresse via les pointeurs.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 14, 16, 25, 36.
*/

#include <stdio.h>

int main(){
    // Char

    char a = 'B';
    char *ptr = &a; // On récupère l'adresse de la valeur de a.

    printf("ptr = %x\n",*ptr); // On affiche la valeur héxadécimal situé à l'adresse du pointeur.

    // Short

    short s = 30000;
    void *sptr = &s; // On récupère l'adresse de la valeur de s.

    printf("sptr = ");
    for (int i=0;i<sizeof(s);i++){
        printf("%x ",*((unsigned char*)sptr+1-i)); // Il est nécessaire de transformer le type du pointeur en char afin d'afficher les valeurs octets par octets en héxadécimal 
    }                                              // car celui-ci est un void.
    printf("\n");

    // Float

    float f = 1;
    void *fptr = &f;

    printf("fptr = ");
    for (int i=0;i<sizeof(f);i++){
        printf("%x ",*((unsigned char*)fptr+3-i)); // +3-i : La mémoire étant organisée en petit-boutiste nous lisons les octets à l'envers afin de les lire dans le bon ordre.
    }                                              // Ici la taille d'un float est de 4 octets nous ajoutons donc 3 au pointeurs.
    printf("\n");


    // Int

    int entier = 30000;
    void *iptr = &entier;

    printf("iptr = ");
    for (int i=0;i<sizeof(entier);i++){
        printf("%x ",*((unsigned char*)iptr+3-i));
    }
    printf("\n");
    

    // Long int

    long int lin = 1234L;
    void *liptr = &lin;

    printf("liptr = ");
    for (int i=0;i<sizeof(lin);i++){
        printf("%x ",*((unsigned char*)liptr+7-i));
    }
    printf("\n");

    // Long long int

    long long int llin = 123456LL;
    void *lliptr = &llin;

    printf("lliptr = ");
    for (int i=0;i<sizeof(llin);i++){
        printf("%x ",*((unsigned char*)lliptr+7-i));
    }
    printf("\n");


    // Double

    double dou = 3E-12;
    void *dptr = &dou;

    printf("dptr = ");
    for (int i=0;i<sizeof(dou);i++){
        printf("%x ",*((unsigned char*)dptr+7-i));
    }
    printf("\n");

    // Long Double

    long double ldou = 3.14E-32;
    void *ldptr = &ldou;

    printf("ldptr = ");
    for (int i=0;i<sizeof(ldou);i++){
        printf("%x ",*((unsigned char*)ldptr+15-i));
    }
    printf("\n");


}