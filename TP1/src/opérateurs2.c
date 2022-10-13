/*
* Nom de fichier : opérateurs2.c
* Objectifs : Réaliser une opération avec l'opérateur entré par l'utilisateur
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 13, 17-24, 26-53
*/

#include <stdio.h> 

int main () {
    int num1= 10;
    int num2= 5;
    char op='~' ;

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
        printf("addition : %i \n",num1+num2);
        break; // permet de ne pas enchaîner sur les cas suivant
        case 2:
        printf("soustration : %i \n",num1-num2);
        break;
        case 3:
        printf("multiplication : %i \n",num1*num2);
        break;
        case 4:
        printf("division : %f \n",(float)num1/num2 );
        break;
        case 5:
        printf("reste : %i \n",num1%num2);
        break;
        case 6:
        printf("Et : %i \n",num1&&num2);
        break;
        case 7:
        printf("Ou : %i \n",num1||num2);
        break;
        case 8:
        printf("~ : %i \n",~num1);
        break;
        case 9:
        printf("L'opérateur n'est pas référencé \n");
    }
    return(0);
}