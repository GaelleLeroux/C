#include <stdio.h> 
#include <limits.h>

int main () {
    printf("sizeof(char) : %lu \n",sizeof(char));
    printf("sizeof(char *) : %lu \n",sizeof(char *));
    printf("sizeof(char **) : %lu \n",sizeof(char **));
    printf("sizeof(char ***)) : %lu \n",sizeof(char ***));

    printf("sizeof(int) : %lu \n",sizeof(int));
    printf("sizeof(int *) : %lu \n",sizeof(int *));
    printf("sizeof(int **) : %lu \n",sizeof(int **));

    printf("sizeof(float) : %lu \n",sizeof(float));
    printf("sizeof(float *) : %lu \n",sizeof(float *));
    printf("sizeof(float **) : %lu \n",sizeof(float **));
    printf("sizeof(float ***) : %lu \n",sizeof(float ***));
    return(0);
}