/*
* Nom de fichier : factorielle.c
* Objectifs : Créer une fonction utilisable dans le main calculant le factorielle.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

# include <stdio.h>

int factorielle(int num){
    if(num==0){
        return 1;
    }
    else {
        return(num*factorielle(num-1));
    }
}
int main(){
    printf("%i",factorielle(3));
    printf("\n");
    return 0;
}