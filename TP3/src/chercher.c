/*
* Nom de fichier : chercher.c
* Objectifs : - Exercice 3.4 : Chercher un entier dans un tableau.
*             - Exercie 3.8 : Chercher une chaine de caractère dans un tableau.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
* Lignes importantes de code : - Exercice 3.4 : 20-24, 28, 29, 35, 37.
*                              - Exercice 3.8 : 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    // Initialisation du tableau
    int a[100];

    // Initialise le générateur pseudo-aléatoire
    srand(time(NULL));
            // Cette étape est obligatoire si on veut que la fonction rand() génère de nouveaux chiffres aléatoirement
            // à chaque relance du programme. Sinon, la graine de l'aléatoire reste la même à chaque compilation, et donc
            // la fonction rand() va générer la même séquence.
            // Ici, on change la graine de l'aléatoire en utilisant l'heure courante (time).

    // Remplissage du tableau
    int n = 0;
    for (int i = 0 ; i < sizeof(a)/4 ; i++){
        n = rand() % 100;   // rand() génère un nombre entre 0 et RAND_MAX définie dans la librairie. On prend le reste
                            // de sa division par 100 pour obtenir un nombre entre 0 et 99 inclu.
        a[i] = n;
    }

    int num;
    printf("Veuillez entrer l'entier recherché : ");
    scanf("%d", &num); // Permet à l'utilisateur d'entrer un nombre dans le terminal

    // Initialisation du pointeur
    void *iptr = &a[0];

    int present = 0;

    for (int i = 0 ; i < sizeof(a)/4 ; i++){
        if (*((int*)iptr+i) == num){
            present = 1;
            break;  // On évite de traverser le tableau pour rien
        }
    }

    if (present == 1){
        printf("Entier présent.\n");
    }
    else{
        printf("Entier non présent.\n");
    }

    // Exercice 3.8


    // Création d'un tableau composé de 10 phrases de taille 30 max.
    char phrase[10][30]={"Bonjour le monde","Au revoir","Salut","Hello le monde","Evann","Gaelle","Arthur","Raphael","Sebastien","Theotime !"}; 

    char string[20];
    printf("Enter the string : ");
    fgets(string,20,stdin);
    printf("\nThe string is : %s",string);

    char mot[30]; // Création de la phrase recherchée.
    printf("Veuillez entrer la phrase recherché : ");
    fgets(mot,30,stdin); 
    printf("La phrase est : %s",mot);

    void *pptr = &phrase[0]; // Initialisation des pointeurs.
    void *mptr = &mot[0];

    mot[strlen(mot)-1]='\0'; // Mise à null du dernier caractère de la phrase

    int present2 = 0; // Condition de sortie

    for (int i=0;i<sizeof(phrase)/30;i++){ // On parcours les phrases
        present2 = 0;
        for (int j=0;j<sizeof(phrase)/10;j++){ // On parcours les chaines de caractères de chaque phrase.

            if ( ((*(((char*)mptr)+j))=='\0') && ((*(((char*)pptr)+i*30+j))=='\0') ) { // Si les 2 phrases ont été lues en entier sans aucune erreur de correspondance
                present2 = 1;                                                          // alors les 2 phrases sont similaires et se finissent en même temps par un null.
                break;                                                                 // On sort de la boucle en mettant la condition de sortie à l'état haut.
            }

            if((*(((char*)pptr)+i*30+j)) != (*(((char*)mptr)+j))) { // Dès que 2 caractères ne correspondent pas on passe au mot suivant.
                break;
            }
            else {
                continue;
            }
        }
        if (present2==1){ // Si la condition de sortie est à l'état haut on arrête de chercher, le mot à été trouvé.
            break;
        }
    }

    if (present2==1){ 
        printf("La phrase a été trouvée. \n");
    }

    else{
        printf("La phrase n'a pas été trouvée. \n");
    }






    return 0;
}
