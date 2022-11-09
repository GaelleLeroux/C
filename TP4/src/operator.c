/*
* Nom de fichier : operator.c
* Objectifs : coder une liste de fonctions utilisables dans main.c.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

# include "operator.h"


int add(int a, int b){
    return a+b;
}

int sous(int a, int b){
    return a-b;
}

int mul(int a, int b){
    return a*b;
}

float divi(int a, int b){
    return (float)a/b;
}

int reste(int a, int b){
    return a%b;
}

int et(int a, int b){
    return a&b;
}

int ou(int a, int b){
    return a|b;
}

unsigned int nega(unsigned int a){
    return ~a;
}