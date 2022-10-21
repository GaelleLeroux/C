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
            if (cpt!=0){
                printf("Ligne %d, %d fois\n",ligne,cpt);
            }
            break;
        }
        if (content == mot[ou]){
            ou +=1;
        }
        else{
            ou = 0;
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
    }
    printf("\n");
    close(fd);
    return 0;
}

int main(int argc, char** argv){
    char* mot = argv[1];
    char* nom_fichier = argv[2];

    lire_fichier(nom_fichier, mot);
}
