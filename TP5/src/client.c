/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

#include "client.h"

int message(int socketfd){
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demandez à l'utilisateur d'entrer un message
  char message[1024];
  printf("Votre message (max 1000 caracteres): ");
  fgets(message, sizeof(message), stdin);
  strcpy(data, "message: ");
  strcat(data, message);

  // Envoie le message au serveur
  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // lire les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  // Affiche le message recus
  printf("Message recu: %s\n", data);

  return 0;
}

int envoie_operateur_numeros(int socketfd){
  char data[1024]; // string qui sera envoyé au serveur
  char message[1024]; // string qui aidera a créer le message dans data
  char classe[1024]; // variable qui contiendra la moyenne de la classe
  memset(classe,0,strlen(classe));
  strcpy(classe,"+ 0 ");
  char content;
  int fd, count, size;
  char nul = '\0';
  void *ctr = &content;
  void *nultr = &nul;

  for (int etu=1;etu<6;etu++){ // on parcours tous les étudiants
    memset(data, 0, sizeof(data)); // on vide data
    char adresse_tempo[1024]; // string qui aide à la création du contenu de adresse
    sprintf(adresse_tempo,"%d",etu);
    char adresse[1024]; // string qui contiendra l'adresse du fichier à lire
    memset(adresse,0,strlen(adresse));
    strcpy(adresse,"../etudiant/");
    strcat(adresse,adresse_tempo);
    strcat(adresse,"/note"); // a la fin de cette ligne adresse vaut : "../etudiantX/note"
                             // avec X le numéro de l'étudiant
    memset(message,0,strlen(message));
    strcpy(message,"+ "); // on commence à créer une partie du message à envoyée
    memset((adresse+18),'\0',5); // ont supprime tous ce qu'il y a dans adresse après ce que l'ont a déjà écrit dedans

    // Initialisation premier nombre du message
    int i =1;
    sprintf(adresse_tempo,"%d",i);
    strcat(adresse_tempo,".txt");
    strcat(adresse,adresse_tempo); // a la fin de cette ligne adresse vaut : "../etudiantX/note1.txt"
    memset(&content,0,sizeof(content));
    fd = open(adresse,O_RDONLY); // on ouvre le fichier
    for(int k=0;k<2;k++){ // ont lit les 2 premiers caractères car les notes sont composée de maximum 2 chiffres
      size = read(fd,&content,1);
      if (size<1){
          break;
      }
      // Lors de la lecture du fichier nous lisons un caractère illisible
      *((char *)ctr+1) = *((char*)nultr); // force le dernier caractère à null
      if (&content!="\n"){
        strcat(message,&content);
      }
    }
    strcat(message," ");
    close(fd);
    

    // on rajoute le deuxième nombre
    for(int i=2;i<6;i++){
      memset((adresse+18),'\0',5); // on met a 0 tous ce qui a après "../etudiantX/note"
      sprintf(adresse_tempo,"%d",i);
      strcat(adresse_tempo,".txt");
      strcat(adresse,adresse_tempo);// a la fin de cette ligne adresse vaut : "../etudiantX/noteI.txt"
                                    // avec I le fichier à lire
      char content;
      int fd, count, size;
      fd = open(adresse,O_RDONLY);
      for(int k=0;k<2;k++){ 
        size = read(fd,&content,1);
        if (size<1){
            break;
        }
        if (&content!="\0"){
          strcat(message,&content);
          // Lors de la lecture du fichier nous lisons un caractère illisible
          message[strlen(message)-1]= '\0'; // Nous forçons le dernier caractère illisible à null
        }
      }
      strcat(message," "); // a la fin de cette ligne message vaut : "+ nmb1 nmb2"
      // avec nmb1 et nmb2 les 2 nombres à additionner.
      close(fd);
      // Création du message data
      memset(data, 0, sizeof(data));
      strcpy(data, "calcul: ");
      strcat(data, message);

      // on l'envoie au serveur
      int write_status = write(socketfd, data, strlen(data));
      if (write_status < 0)
      {
        perror("erreur ecriture");
        exit(EXIT_FAILURE);
      }
      // on lit la réponse
      memset(data,'0',strlen(data));
      int read_status = read(socketfd, data, sizeof(data));
      if (read_status < 0)
      {
        perror("erreur lecture");
        return -1;
      }
      // réarrange le message pour addition le prochain nombre
      memset(message,'\0',strlen(message));
      strcpy(message,"+ ");
      strcat(message,&data[8]); // ont lit la réponse de l'addition et ont le met dans message
      strcat(message," ");
    }
    // réarrange message pour la division et donc le calcul de la moyenne
    memset(message,'\0',strlen(message));
    strcpy(message,"/ ");
    strcat(message,&data[8]);
    strcat(message," ");
    int j = 5;
    char tempo_div[1024];
    memset(tempo_div,'0',strlen(tempo_div));
    sprintf(tempo_div,"%d",j);
    strcat(message,tempo_div);
    memset(data, 0, sizeof(data));
    strcpy(data, "calcul: ");
    strcat(data, message); // A la fin de cette ligne data vaut : ""

    int write_status = write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
      perror("erreur ecriture");
      exit(EXIT_FAILURE);
    }
    // on lit la réponse
    memset(data, 0, sizeof(data));
    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
      perror("erreur lecture");
      return -1;
    }

    printf("Moyenne eleve %d: %s\n",etu, &data[8]);
    memset(message,'\0',strlen(message));

    // moyenne de la classe
    strcat(classe,&data[8]);
    memset(data, 0, sizeof(data));
    strcpy(data, "calcul: ");
    strcat(data, classe);

    // on ecrit pour la somme de la moyenne de la classe
    write_status = write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
      perror("erreur ecriture");
      exit(EXIT_FAILURE);
    }

    // on lit la réponse pour la moyenne de la classe
    memset(data, 0, sizeof(data));
    read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
      perror("erreur lecture");
      return -1;
    }
    memset(classe, 0,strlen(classe));
    strcpy(classe,"+ ");
    strcat(classe,&data[8]);
    strcat(classe," ");


  }
  memset(classe,0,strlen(classe));
  strcpy(classe,&data[8]);
  memset(data, 0, sizeof(data));
  strcpy(data, "calcul: / ");
  strcat(data, classe);
  strcat(data," 5");

  // on ecrit pour la division de la moyenne de la classe
  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // on lit la réponse pour la division de la moyenne de la classe
  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Moyenne classe: %s\n", &data[8]);
  memset(message,'\0',strlen(message));
  strcpy(message,"fin");
  memset(data, 0, strlen(data));
  strcpy(data, "calcul: ");
  strcat(data, message);

  write_status = write(socketfd, data, strlen(data));
  write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;

}

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(int socketfd)
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demandez à l'utilisateur d'entrer un message
  char message[1024];
  printf("Votre calcul (une lettre est considérée comme valant 0): ");
  fgets(message, sizeof(message), stdin);
  strcpy(data, "calcul: ");
  strcat(data, message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // lire les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu: %s\n", data);

  return 0;
}

int main()
{
  int socketfd;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  //appeler la fonction pour envoyer un message au serveur
  printf("Exercice 5.4\n");
  message(socketfd);

  printf("Exercice 5.5\n");
  char diviser = '%';
  printf("Opérateurs disponible : + * - / %c \n",diviser);
  envoie_recois_message(socketfd);

  printf("\n");
  printf("Exercice 5.6\n");
  envoie_operateur_numeros(socketfd);

  return 0;
}