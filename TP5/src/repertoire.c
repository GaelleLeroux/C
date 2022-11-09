/*
* Nom de fichier : repertoire.c
* Objectifs : - Exercice 5.1 : Affiche les fichier présent dans un répertoire.
*             - Exercice 5.2 : Parcourt le répertoire en récursif et affiche tous les noms
                               des fichiers, des répertoires, des sous-répertoires et des
                               fichiers dans les sous-répertoires.
              - Exercice 5.3 : Parcourt le répertoire en itératif et affiche tous les noms
                               des fichiers, des répertoires, des sous-répertoires et des 
                               fichiers dans les sous-répertoires.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : - Exercice 5.1 : 29, 38, 39, 42.
*                              - Exercice 5.2 : 32, 66, 70, 72-80.
*                              - Exercice 5.3 : 92, 99, 104, 105, 107.
*/

# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "repertoire.h"

// Exercice 5.1
void lire_dossier(const char * repertoire){
    printf("on veut lire : %s \n",repertoire);
    DIR *dirp ;
    struct dirent * ent;

    dirp = opendir(repertoire); // on ouvre le repertoire

    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

    
    while(1){
        ent = readdir(dirp); // ont lit un nom de fichier du repertoire
        if (ent == NULL){ // si il est nul nous somme arrivé à la fin du répertoire
            break;
        }
        printf("%s ",ent->d_name); // on affiche le nom du fichier
    }
    closedir(dirp);

}

// Exercice 5.2
void lire_dossier_recursif(char *repertoire){
    printf("%s :\n",repertoire);
    DIR *dirp ;
    struct dirent * ent;

    dirp = opendir(repertoire); // On ouvre le répertoire
    
    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

    while(1){
        ent = readdir(dirp); // ont lit un fichier
        if (ent == NULL){ // si il est null nous somme arrivé au bout du répertoire
            break; // nous sortons donc de la boucle
        }
        if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")){
            continue; // on ne prend pas en compte . et .. present dans les répertoires
        }
        printf("%s ",ent->d_name);
        if (ent->d_type==4){ // si le fichier est repertoire
            printf("\n");
            // on créer une nouvelle variable "new-repertoire", on la vide avec la memset
            // on lui affecte la nouvelle adresse du répertoire que l'on veut lire
            // on rappelle la fonction pour lire le répertoire
            char *new_repertoire = malloc(strlen(repertoire)+2+strlen(ent->d_name));
            memset(new_repertoire,0,strlen(repertoire)+2+strlen(ent->d_name));
            strcat(new_repertoire,repertoire);
            strcat(new_repertoire,"/");
            strcat(new_repertoire,ent->d_name);
            lire_dossier_recursif(new_repertoire);
        }
        
    }
    printf("\n");
    closedir(dirp);
}

// Exercice 5.3
void lire_dossier_iteratif(char *repertoire){
    printf("%s :\n",repertoire);
	DIR *dirp = opendir(repertoire); // ouvre le repertoire

    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

	chdir(repertoire); // change le répertoire de travail courant
	struct dirent *ent;

	while(ent = readdir(dirp)){

		if (strcmp(ent->d_name, ".") & strcmp(ent->d_name, "..")){ // on ne prend pas en compte . et .. present dans les répertoires
			printf("%s \n", ent->d_name); // on affiche le nom du fichier

			if (ent->d_type == 4){ // si c'est un repertoire on recommence
				DIR *dirp2 = opendir(ent->d_name);
				struct dirent *ent2;

				while(ent2 = readdir(dirp2)){

					if (strcmp(ent2->d_name, ".") & strcmp(ent2->d_name, "..")){
							printf("%s   ", ent2->d_name);
				    }
                }
                printf("\n \n");
			}
		}
	}	
}
    
    


int main(){
    printf("Exercice 5.1 :\n");
    lire_dossier(".");
    printf("\n\nExercicre 5.2 : \n");
    lire_dossier_recursif("..");
    printf("\n\nExercicre 5.3 : \n");
    lire_dossier_iteratif("..");
    return(0);
}
