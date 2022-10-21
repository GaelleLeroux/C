# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
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
        printf("%s\n",ent->d_name);
    }
    closedir(dirp);

}

int main(){
    lire_dossier(".");
    return(0);
}
