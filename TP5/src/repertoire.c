# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "repertoire.h"

void lire_dossier(const char * repertoire){
    printf("on veut lire : %s \n",repertoire);
    DIR *dirp ;
    struct dirent * ent;

    dirp = opendir(repertoire);

    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

    
    while(1){
        ent = readdir(dirp);
        if (ent == NULL){
            break;
        }
        printf("%s ",ent->d_name);
        printf("%i\n",ent->d_type);
    }
    closedir(dirp);

}

void lire_dossier_recursif(char *repertoire){
    printf("on veut lire : %s \n",repertoire);
    DIR *dirp ;
    struct dirent * ent;

    dirp = opendir(repertoire);
    
    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

    while(1){
        ent = readdir(dirp);
        if (ent == NULL){
            break;
        }
        if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")){
            continue;
        }

        if (ent->d_type==4){
            repertoire = malloc(sizeof(repertoire)+10);
            strcat(repertoire,"./.");
            strcat(repertoire,ent->d_name);
            printf("repertoire : %s\n",repertoire);
            lire_dossier_recursif(repertoire);
        }
        printf("%s\n",ent->d_name);
        
    }
    closedir(dirp);
    }

    
    
    


int main(){
    //lire_dossier(".");
    lire_dossier_recursif("..");
    return(0);
}
