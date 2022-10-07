/*
* Nom de fichier : etudiants2.c
* Objectifs : Créer un tableau étudiant pour la gestion de données en utilisant struct.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 12, 19, 21.
*/

#include <stdio.h>
#include <string.h>

int main(){
    // Initialisation du tableau
    typedef struct details{ // Création de la structure détails.
        char prenom[30];
        char nom[30];
        char adresse[30];
        short module1;
        short module2;
    } details;

    details etudiant[5]; // Définition de la taille de la structure.
    // Etudiant 1
    strcpy(etudiant[0].prenom, "Evann"); // Affectation des éléments dans la structure.
    strcpy(etudiant[0].nom, "Nalewajek");
    strcpy(etudiant[0].adresse, "Villeurbanne");
    etudiant[0].module1 = 1;
    etudiant[0].module2 = 2;
    // Etudiant 2
    strcpy(etudiant[1].prenom, "Gaelle");
    strcpy(etudiant[1].nom, "Leroux");
    strcpy(etudiant[1].adresse, "Villeurbanne");
    etudiant[1].module1 = 19;
    etudiant[1].module2 = 17;
    // Etudiant 3
    strcpy(etudiant[2].prenom, "Jacques");
    strcpy(etudiant[2].nom, "Chirac");
    strcpy(etudiant[2].adresse, "Paris");
    etudiant[2].module1 = 13;
    etudiant[2].module2 = 12;
    // Etudiant 4
    strcpy(etudiant[3].prenom, "Elon");
    strcpy(etudiant[3].nom, "Musk");
    strcpy(etudiant[3].adresse, "Mars");
    etudiant[3].module1 = 8;
    etudiant[3].module2 = 6;
    // Etudiant 5
    strcpy(etudiant[4].prenom, "Jeff");
    strcpy(etudiant[4].nom, "Bezos");
    strcpy(etudiant[4].adresse, "Amazon");
    etudiant[4].module1 = 15;
    etudiant[4].module2 = 18;

    for (int i = 0; i < 5; i++){
        printf("Prénom : %s, Nom : %s, Adresse : %s, Note Module 1 : %d, Note Module 2 : %d\n", etudiant[i].prenom, etudiant[i].nom, etudiant[i].adresse, etudiant[i].module1, etudiant[i].module2);
    }
    return 0;
}