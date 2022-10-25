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


int moyenne_demande(int socketfd){
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  char adresse[1024];
  strcpy(adresse,"../etudiant/1/note1.txt");
  char message[1024];
  memset(message,0,sizeof(message));
  strcpy(message,"+ ");
  char adresse_tempo[1024];
  memset((adresse+18),'\0',5);
  // Initialisation premier nombre du message 
  int i = 1;
  sprintf(adresse_tempo,"%d",i);
  strcat(adresse_tempo,".txt");
  strcat(adresse,adresse_tempo);
  printf("adresse : %s\n",adresse);
  char content;
  int fd, count, size;
  fd = open(adresse,O_RDONLY);
  for(int k=0;k<2;k++){
      size = read(fd,&content,1);
      if (size<1){
          break;
      }
      if (&content!="\n"){strcat(message,&content);}
  }
  strcat(message," ");
  //printf("le premier 3 : %c\n",message[3]);
  close(fd);
  

  // on rajoute le deuxième nombre
  for(int i=3;i<6;i++){
    //printf("le message pr l'instant : %s",message);
    memset((adresse+18),'\0',5);
    sprintf(adresse_tempo,"%d",i);
    strcat(adresse_tempo,".txt");
    strcat(adresse,adresse_tempo);
    printf("adresse 2 : %s\n",adresse);
    char content;
    int fd, count, size;
    fd = open(adresse,O_RDONLY);
    for(int k=0;k<2;k++){
      size = read(fd,&content,1);
      if (size<1){
          break;
      }
      if (&content!="\n"){strcat(message,&content);}
  }
    strcat(message," ");
    close(fd);
    printf("le message a la fin: %s\n",message);
    printf("le message a la fin: %c\n",message[1]);
    printf("le message a la fin: %c\n",message[2]);
    printf("le message a la fin: %c\n",message[3]);
    printf("le message a la fin: %c\n",message[4]);
    printf("le message a la fin: %c\n",message[5]);
    printf("le message a la fin: %c\n",message[6]);
    printf("le message a la fin: %c \n",message[7]);
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
    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
      perror("erreur lecture");
      return -1;
    }
    printf("data : %s\n",data);
    // réarrange le message pour addition le prochain nombre
    memset(message,'\0',strlen(message));
    strcpy(message,"+ ");
    strcat(message,&data[9]);
    strcat(message,&data[10]);
    strcat(message,&data[11]);
    printf("message 3 fin for : %s\n",message);
  }
  memset(message,'\0',strlen(message));
  strcpy(message,"/ ");
  strcat(message,data);
  strcat(message," ");
  int j = 5;
  char tempo_div[1024];
  sprintf(tempo_div,"%d",j);
  strcat(message,tempo_div);
  memset(data, 0, sizeof(data));
  strcpy(data, "calcul: ");
  strcat(data, message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }
  // on lit la réponse
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Moyenne eleve 1: %s\n", data);
  memset(message,'\0',strlen(message));
  strcpy(message,"fin");
  memset(data, 0, sizeof(data));
  strcpy(data, "calcul: ");
  strcat(data, message);

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
  envoie_recois_message(socketfd);

  //moyenne_demande(socketfd);

  //close(socketfd);
  return 0;
}
