#include <stdio.h>

int main(){
    char Prenom[5][30] = {"Evann", "Gaelle","Jacques", "Elon", "Jeff"};
    char Nom[5][30] = {"Nalewajek", "Leroux","Chirac", "Musk", "Bezos"};
    char Adresse[5][30] = {"Villeurbanne", "Villeurbanne","Paris", "Mars", "Amazon"};
    short Module1[5] = {1, 19, 13, 8, 15};
    short Module2[5] = {2, 17, 12, 6, 18};
    
    for (int i = 0; i < 5; i++){
        printf("Prénom : %s, Nom : %s, Adresse : %s, Note Module 1 : %d, Note Module 2 : %d\n", Prenom[i], Nom[i], Adresse[i], Module1[i], Module2[i]);
    }
    return 0;
}