/*
* Nom de fichier : chercherfichier.c
* Objectifs : Chercher un mot dans un fichier, et renvoyer la ligne et le nombre
*             de fois où il apparaît.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

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
    // Entier servant à compter le nombre de fois où le mot apparaît sur une ligne.
    int cpt = 0;
    int taille = strlen(mot);
    // Entier servant à compter le nombre de lettre en commun avec le mot recherché.
    int compare = 0;
    // Entier servant à situation la ligne que la boucle est en train de lire.
    int ligne = 1;
    while(1){
        size = read(fd,&content,1);
        if (size<1){
            if (cpt!=0){
                printf("Ligne %d, %d fois\n",ligne,cpt);
            }
            break;
        }
        if (content == mot[compare]){
            compare +=1;
        }
        else{
            compare = 0;
        }
        if (compare == taille){
            cpt+=1;
            compare = 0;
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
