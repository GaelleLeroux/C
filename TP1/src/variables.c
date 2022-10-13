/*
* Nom de fichier : variables.c
* Objectifs : Afficher dans la console tous les types de variables avec printf
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : 11-23, 25-37
*/

#include <stdio.h> 

int main () {
    char ch = 'A';
    unsigned char uch = 234;
    short sh = -12;
    unsigned short ush = 6589;
    int in = 2;
    unsigned int uin = 2563;
    long int lin = 1234L;
    unsigned long int ulin = 1234567L;
    long long int llin = 123456LL;
    unsigned long long int ullin = 1234567891011121314L;
    float fl = 3.14;
    double dou = 3.14E-12;
    long double ldou = 3.14E-32;

    printf("char : %c \n",ch);
    printf("unsigned char : %hhu \n",uch);
    printf("short : %hd \n",sh);
    printf("unsigned short : %hu \n",ush);
    printf("int : %d \n",in);
    printf("unsigned int : %u \n",uin);
    printf("long int : %ld \n",lin);
    printf("unsigned long int : %lu \n",ulin);
    printf("long long int : %lld \n",llin);
    printf("unsigned long long int : %llu \n",ullin);
    printf("float : %f \n",fl);
    printf("double : %g \n",dou);
    printf("long double : %Lg \n",ldou);

    return(0);
}