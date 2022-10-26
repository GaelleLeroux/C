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
        if (ent == NULL){
            break;
        }
        if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")){
            continue;
        }
        printf("%s ",ent->d_name);
        if (ent->d_type==4){
            printf("\n");
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

void lire_dossier_iteratif(char *repertoire){
    printf("%s :\n",repertoire);
	DIR *dirp = opendir(repertoire);

    if (dirp == NULL){
        perror("opendir");
        //return(EXIT_FAILURE);
    }

	chdir(repertoire);
	struct dirent *ent;

	while(ent = readdir(dirp)){

		if (strcmp(ent->d_name, ".") & strcmp(ent->d_name, "..")){
			printf("%s \n", ent->d_name);

			if (ent->d_type == 4){
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
    //lire_dossier(".");
    //lire_dossier_recursif("..");
    lire_dossier_iteratif("..");
    return(0);
}
