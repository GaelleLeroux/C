/*
* Nom de fichier : fichier.c
* Objectifs : Coder deux fonctions utilisables dans main.c :
              l'une servant à lire un fichier, l'autre à écrire dans le fichier.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

# include "fichier.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>


char lire_fichier(char *nom_de_fichier){
    char content;
    int fd, count, size;
    fd = open(nom_de_fichier,O_RDONLY);
    // La boucle va lire le fichier lettre par lettre.
    while(1){
        size = read(fd,&content,1);
        if (size<1){
            break;
        }
        printf("%c",content);
    }
    printf("\n");
    close(fd);
    return 0;
}

char ecrire_dans_fichier(char *nom_de_fichier, char *content){
    int fd, count, size;
    // On ouvre le fichier selon le nom.
    // Si le fichier n'existe pas, on le créer, sous format ".txt" par défaut.
    fd = open(nom_de_fichier,O_CREAT|O_WRONLY|O_APPEND,S_IRUSR|S_IWUSR);
    size = write(fd, content, strlen(content));
    close(fd);
    return 0;
}