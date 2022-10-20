# include <stdio.h>
# include <stdlib.h>
# include "operator.h"
# include "fichier.h"
# include <time.h>
# include "liste.h"

int main() {
    int num1= 4;
    int num2= 3;
    char op='+' ;

    
    int a = 9; // Si l'opérateur n'est pas référencé, un message d'erreur apparaît (cas n°9)

    if(op=='+'){a=1;}
    if(op=='-'){a=2;}
    if(op=='*'){a=3;}
    if(op=='/'){a=4;}
    if(op=='%'){a=5;}
    if(op=='&'){a=6;}
    if(op=='|'){a=7;}
    if(op=='~'){a=8;}


    switch(a) {
        case 1: 
        printf("addition : %d \n",add(num1,num2));
        break; // permet de ne pas enchaîner sur les cas suivant
        case 2:
        printf("soustration : %i \n",sous(num1,num2));
        break;
        case 3:
        printf("multiplication : %i \n",mul(num1,num2));
        break;
        case 4:
        printf("division : %f \n",divi(num1,num2));
        break;
        case 5:
        printf("reste : %i \n",reste(num1,num2));
        break;
        case 6:
        printf("Et : %i \n",et(num1,num2));
        break;
        case 7:
        printf("Ou : %i \n",ou(num1,num2));
        break;
        case 8:
        printf("~ : %u \n",nega(num1));
        break;
        case 9:
        printf("L'opérateur n'est pas référencé \n");
    }

    ///////////////////////////////////////////////////////////////////////
    // Exercice 2
    //lire_fichier("./message.txt");

    //ecrire_dans_fichier("./message.txt"," Hola");

    ///////////////////////////////////////////////////////////////////////
    // Exercice 7

    srand(time(NULL));

    int nbr_couleurs = 10;
    struct couleur TableauCouleurs[nbr_couleurs];

    for(int i = 1; i < nbr_couleurs; i++){
        printf("%hhu", TableauCouleurs[i].rouge);
        TableauCouleurs[i].rouge = rand() % 256;
        TableauCouleurs[i].vert = rand() % 256;
        TableauCouleurs[i].bleu = rand() % 256;
        TableauCouleurs[i].alpha = rand() % 256;
    }

    struct liste_couleurs *liste;
    liste = malloc(sizeof(liste));
    int cpt = nbr_couleurs;
    int j = 0;
    while(cpt != 0){
        cpt--;
        insertion(&TableauCouleurs[j], liste);
        j++;
    }
    parcours(liste);
    return 0;
}
