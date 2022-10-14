# include <stdio.h>
# include <stdlib.h>
# include "operator.h"


int main(int argc, char ** argv){
    int a = 9; // Si l'opérateur n'est pas référencé, un message d'erreur apparaît (cas n°9)

    char op = argv[1][0];
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);

    switch(op) {
        case '+': 
        printf("addition : %d \n",add(num1,num2));
        break; // permet de ne pas enchaîner sur les cas suivant
        case '-':
        printf("soustration : %i \n",sous(num1,num2));
        break;
        case '*':
        printf("multiplication : %i \n",mul(num1,num2));
        break;
        case '/':
        printf("division : %f \n",divi(num1,num2));
        break;
        case '%':
        printf("reste : %i \n",reste(num1,num2));
        break;
        case '&':
        printf("Et : %i \n",et(num1,num2));
        break;
        case '|':
        printf("Ou : %i \n",ou(num1,num2));
        break;
        case '~':
        printf("~ : %u \n",nega(num1));
        break;
    }
    return(0);
}