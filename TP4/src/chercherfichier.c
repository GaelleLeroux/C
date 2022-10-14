# include <stdio.h>
# include "fichier.h"

char lire_fichier(char *nom_de_fichier, char* mot){
    char content;
    int fd, count, size;
    fd = open(nom_de_fichier,O_RDONLY);
    int i = 1;
    int taille = strlen(mot);
    while(1){
        size = read(fd,&content,1);
        if (size<1){
            break;
        }
        if (content=='\n'){
            i+=1;
        }
        printf("%c",content);
    }
    printf("\n");
    printf("I vaut %d",i);
    close(fd);
    return 0;
}

int main(int argc, char** argv){
    char mot = argv[2][0];
    char nom_fichier = argv[1][0];

    lire_fichier(nom_de_fichier);



}