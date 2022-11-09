# include <stdio.h>
# include <stdlib.h>
# include "operator.h"
# include "fichier.h"
# include <time.h>
# include "liste.h"

int main() {

    ///////////////////////////////////////////////////////////////////////
    // Exercice 1 : operator.c et operator.h
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
    // Exercice 2 : fichier.c et fichier.h
    lire_fichier("./message.txt");

    ecrire_dans_fichier("./message.txt"," Hola");

    ///////////////////////////////////////////////////////////////////////
    // Exercice 7 : liste.c et liste.h

    srand(time(NULL));

    int nbr_couleurs = 10;
    struct liste_couleurs *liste;
    liste = malloc(sizeof(struct liste_couleurs));

    // Initialisation de la première couleur de liste
    struct couleur *premiere_couleur;
    premiere_couleur = malloc(sizeof(struct couleur));
    premiere_couleur->rouge = rand() %256;
    premiere_couleur->vert = rand() %256;
    premiere_couleur->bleu = rand() %256;
    premiere_couleur->alpha = rand() %256;
    liste->couleur = premiere_couleur;

    int cpt = nbr_couleurs;
    
    // On ajoute à chaque boucle une nouvelle couleur aléatoire, selon le nombre de couleur que l'on veut.
    while(cpt != 1){
        cpt--;
        struct couleur *new_color;
        new_color = malloc(sizeof(struct couleur));
        new_color->rouge = rand() %256;
        new_color->vert = rand() %256;
        new_color->bleu = rand() %256;
        new_color->alpha = rand() %256;
        insertion(new_color, liste);
    }
    parcours(liste);
    return 0;
}
