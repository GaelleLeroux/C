#include <stdio.h>

int main(){
    char phrase1[] = "Bonjour le monde !";

    // Calcul du nombre de caractères
    int i = 0;
    while (phrase1[i] != '\0'){
        i += 1;
    }
    printf("\nNombre de caractères : %d\n", i);

    // Copie d'une chaîne de caractère
    char copie[sizeof(phrase1)];

    for (int u=0; u<i+1;u++){
        copie[u] = '\0';
    } // Vide la chaîne de charactères "copie"

    for(int i = 0; i+1 < sizeof(phrase1);i++){
        copie[i] = phrase1[i];
    }
    printf("Copie = %s\n", copie);

    // Concaténation de deux chaînes de char

    char phrase2[] = " Au revoir !";
    int j = 0;
    while (phrase2[j] != '\0'){
        j += 1;
    }
    char concat[i+j];
    for (int u=0; u<i+j+1;u++){
        concat[u] = '\0';
    } // Vide la chaîne de caractères "concat"

    i = 0;
    for(i; i+1 < sizeof(phrase1);i++){
        concat[i] = phrase1[i];
    }

    j = 0;
    for(j; j+1 < sizeof(phrase2);j++){
        concat[i+j] = phrase2[j];
    }
    printf("Concatenation = %s\n\n", concat);
    return 0;
}