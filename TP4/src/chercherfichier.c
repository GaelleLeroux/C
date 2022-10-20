# include <stdio.h>
# include "fichier2.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

char lire_fichier(char *nom_de_fichier,char *mot){
    char content;
    int fd, count, size;
    fd = open(nom_de_fichier,O_RDONLY);
    int cpt = 0;
    int taille = strlen(mot);
    int ou = 0;
    int ligne = 1;
    while(1){
        size = read(fd,&content,1);
        if (size<1){
            break;
        }
        if (content == mot[ou]){
            ou +=1;
        }
        if (ou == taille){
            cpt+=1;
            ou = 0;
        }
        if (content=='\n'){
            if (cpt!=0){
                printf("Ligne %d, %d fois\n",ligne,cpt);
            }
            ligne +=1;
            cpt=0;
        }
        //printf("%c",content);
    }
    printf("\n");
    close(fd);
    return 0;
}

int main(int argc, char** argv){
    char mot = argv[2][0];
    char nom_fichier = argv[1][0];

    lire_fichier("./message.txt","Hola");



}