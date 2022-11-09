/*
* Nom de fichier : etudiant_bd.c
* Objectifs : Ecrire dans un fichier texte toutes les informations des 5 étudiants.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

# include "fichier.h"
#include <stdio.h>
#include <string.h>

int main(){
    // Initialisation du tableau
    typedef struct details{ // Création de la structure détails.
        char prenom[30];
        char nom[30];
        char adresse[30];
        char module1[30];
        char module2[30];
    } details;

    details etudiant[2]; // Définition de la taille de la structure.

    for (int i = 0;i<2;i++){
        char prenom[30];
        printf("Prenom : ");
        scanf("%s",prenom);
        strcpy(etudiant[i].prenom, prenom);
        ecrire_dans_fichier("./etudiant.txt",prenom);
        ecrire_dans_fichier("./etudiant.txt"," ");

        char nom[30];
        printf("nom : ");
        scanf("%s",nom);
        strcpy(etudiant[i].nom, nom);
        ecrire_dans_fichier("./etudiant.txt",nom);
        ecrire_dans_fichier("./etudiant.txt"," ");

        char adresse[30];
        printf("adresse : ");
        scanf("%s",adresse);
        strcpy(etudiant[i].adresse, adresse);
        ecrire_dans_fichier("./etudiant.txt",adresse);
        ecrire_dans_fichier("./etudiant.txt"," ");
        

        char note1[30];
        printf("note1 : ");
        scanf("%s",note1);
        strcpy(etudiant[i].module1, note1);
        ecrire_dans_fichier("./etudiant.txt",note1);
        ecrire_dans_fichier("./etudiant.txt"," ");

        char note2[30];
        printf("note2 : ");
        scanf("%s",note2);
        strcpy(etudiant[i].module2, note2);
        ecrire_dans_fichier("./etudiant.txt",note2);
        ecrire_dans_fichier("./etudiant.txt"," ");

        ecrire_dans_fichier("./etudiant.txt","\n");
        }

        lire_fichier("./etudiant.txt");


    return 0;

}