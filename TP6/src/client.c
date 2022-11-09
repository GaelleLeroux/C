/*
* Nom de fichier : client.c
* Objectifs : Envoyer les données entrées par l'utilisateur au serveur.
*             En fonction des données, le programme doit reconnaître tout seul
*             si l'utilisateur souhaite envoyer un message, faire un calcul, ou
*             connaître les couleurs prédominantes d'une image.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

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

#include "client.h"
#include "bmp.h"

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */
int envoie_calcul(int socketfd, char* op,char * nmb1, char* nmb2){
  // On rassemble les données sous format JSON
  char data[1024];
  memset(data,0,1024);
  strcat(data,"[{\"code\": \"calcul\", \"valeurs\": [\"");
  strcat(data,op);
  strcat(data,"\",\"");
  strcat(data,nmb1);
  strcat(data,"\",\"");
  strcat(data,nmb2);
  strcat(data,"\"]}]");

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
  printf("Message recus : %s\n",data);
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }
  char *str = data;
  while(str){
    str = strstr(str, "\"valeurs\"");
    if (str == NULL) {
            break;
        }
    str = strchr(str, ':');
        if (str == NULL) {
            break;
        }
    str++;
    str++;
    str++;
    str++;
    printf("Résultat : ");
    while(*str!='\"'){
      printf("%c",*str);
      str++;
    }
    printf("\n");
  }

  return 0;
}


int envoie_recois_message(int socketfd){
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demander à l'utilisateur d'entrer un message
  char message[1024];
  memset(message,'0',1024);
  printf("Votre message (max 1000 caracteres): ");
  fgets(message, sizeof(message), stdin);
  strcat(data,"[{\"code\": \"message\", \"valeurs\": [\"");
  memset(message+strlen(message)-1,0,1);
  strcat(message,"\"]}]");
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
  printf("Message recus : %s\n",data);
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }
  char* str = data;
  str = strstr(str, "\"valeurs\"");
  str = strchr(str, ':');
  str++;
  str++;
  str++;
  str++;
  printf("Lecture du message: ");
  while (*str != '\"') {
    printf("%c",*str);
    str++;
  }
  printf("\n");

  return 0;
}

void analyse(char *pathname, char *data, int nmb_int){
  // compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  char temp_string[10] = "10" ;
  if (cc->size < 10)
  {
    sprintf(temp_string, "%d,", cc->size);
  }
  // On rassemble les données sous format JSON
  char nmb_char[10];
  memset(nmb_char,'0',strlen(nmb_char));
  sprintf(nmb_char,"%d",nmb_int);
  strcat(data,"[{\"code\": \"couleurs\", \"valeurs\": [\"");
  strcat(data,nmb_char);
  strcat(data,"\",\"");


  // choisir 10 couleurs
  for (count = 1; count < nmb_int+1 && cc->size - count > 0; count++)
  {
    if (cc->compte_bit == BITS32)
    {
      sprintf(temp_string, "#%02x%02x%02x", cc->cc.cc24[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    if (cc->compte_bit == BITS24)
    {
      sprintf(temp_string, "#%02x%02x%02x", cc->cc.cc32[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    strcat(data, temp_string);
    strcat(data,"\",\"");
  }

  // enlever la dernière virgule
  data[strlen(data) - 1] = '\0';
  data[strlen(data) - 2] = '\0';
  strcat(data,"\"]}]");
  printf("\n");
  printf("data : %s\n",data);
}

int envoie_couleurs(int socketfd, char *pathname, char * nmb)
{
  // Initialisation avant l'analyse
  char data[1024];
  memset(data, 0, sizeof(data));
  int nmb_int = atoi(nmb);

  analyse(pathname, data, nmb_int);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}

int main(int argc, char **argv)
{
  int socketfd;

  struct sockaddr_in server_addr;

  // Cas 1 : le client ne met aucun argument, la fonction renvoie donc une erreur
  if (argc < 2)
  {
    printf("usage: ./client chemin_bmp_image\n");
    return (EXIT_FAILURE);
  }

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

  /* Cas 2 :
  *  Par élimination : Si le client ne veut pas recevoir les couleurs prédominantes
  *  ni réaliser un calcul, alors il veut forcément écrire un message.
  */
  if ((argc != 3) && (argc !=4))
  {
    // envoyer et recevoir un message
    envoie_recois_message(socketfd);
  }

  // Cas 3 : le client veut recevoir les couleurs prédominantes d'une image
  if(argc==3)
  {
    // envoyer et recevoir les couleurs prédominantes
    // d'une image au format BMP (argv[1])
    int nmb = atoi(argv[2]);
    if (nmb<31){
    envoie_couleurs(socketfd, argv[1],argv[2]);
    }
    else{
      printf("Nombre de couleur trop grand\n");
    }
  }

  // Cas 4 : le client veut réaliser un calcul
  if (argc==4){
    envoie_calcul(socketfd,argv[1],argv[2],argv[3]);
  }

  close(socketfd);
}