#include <stdio.h> 

int main () {

    printf("\n Divisible par 2 et 15 \n");
    for (int numero = 1;numero<1001;numero++){
        if (numero%2==0){
            if (numero%15==0){
                printf("%d  ",numero);
            }   
        }
        continue; // Il n'a pas grand intérêt...

    }
    
    printf("\n Divisible par 103 ou 107 \n");
    for (int numero = 1;numero<1001;numero++){
        if (numero%103==0){
            printf("%d  ",numero);
            continue; // La première condition est suffisante, continue permet de sauter la deuxième condition et de passer au nombre suivant
        }
        if (numero%107==0){
            printf("%d  ",numero);
            }  
    }

    printf("\n Divisible par 5 ou 7 mais pas 3 \n");
    for (int numero = 1;numero<1001;numero++){
        if (numero%3==0){
            continue; // idem 
        }
        if (numero%5==0){
            printf("%d  ",numero);
            continue; // idem
        }
        if (numero%7==0){
            printf("%d  ",numero);
            }  
    }
    return(0);
}