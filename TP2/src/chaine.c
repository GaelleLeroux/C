#include <stdio.h>

int main(){
    char a[] = "ab jaj cd";

    // Calcul du nombre de caractères
    printf("a = %ld\n",sizeof(a)-1);

    // Copie d'une chaîne de caractère
    char b[sizeof(a)];
    for(int i = 0; i+1 < sizeof(a);i++){
        b[i] = a[i];
    }
    printf("%s\n", b);

    // Concaténation de deux chaînes de char
    char c[sizeof(a)+sizeof(b)];
    for(int i = 0; i < sizeof(a);i++){
        c[i] = a[i];
    }
    printf("%s\n", c);
    for(int i = 0; i < sizeof(b);i++){
        c[i+sizeof(a)] = b[i];
    }
    printf("c = %ld\n",sizeof(c)-2);
    printf("%s\n", c);
    return 0;
}