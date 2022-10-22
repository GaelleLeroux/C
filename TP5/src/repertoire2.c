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
    printf("%s :\n",repertoire);
    DIR *dirp ;
    struct dirent * ent;

    dirp = opendir(repertoire);
    
    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

    while(1){
        ent = readdir(dirp);
        char *wait=malloc(1);
        memset(wait,0,1);
        int j = 0;
        if (ent == NULL && wait == NULL){
            break;
        }
        if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")){
            continue;
        }

        printf("%s ",ent->d_name);

        if (ent == NULL && j!=0){
            char *nom = malloc(strlen(wait)+1);
            memset(nom,0,strlen(wait)+1);
            int i =1;
            while(j!=0){
                i+=1;
                memset(nom,0,strlen(wait)+1);
                while(!strcmp(wait[i],'0')){
                    strcat(nom,wait[i]);
                }
                j-=1;
                lire_dossier_recursif(nom);
            }

        }
        if (ent->d_type==4){
            char *new_repertoire = malloc(strlen(repertoire)+2+strlen(ent->d_name));
            memset(new_repertoire,0,strlen(repertoire)+2+strlen(ent->d_name));
            strcat(new_repertoire,repertoire);
            strcat(new_repertoire,"/");
            strcat(new_repertoire,ent->d_name);
            j+=1;
            char *wait2 = malloc(strlen(wait)+strlen(new_repertoire)+2);
            memset(wait2,0,strlen(wait)+2+strlen(new_repertoire));
            strcat(wait2,wait);
            strcat(wait2,'0');
            strcat(wait2,new_repertoire);
            wait = wait2;

        }
        }
        
    
    printf("\n");
    closedir(dirp);
    }

    
    
    


int main(){
    //lire_dossier(".");
    lire_dossier_recursif("..");
    return(0);
}
