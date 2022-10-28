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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int envoie_couleurs(int socketfd, char *pathname, char * nmb);


char *str = "[{\"code\": \"message\", \"valeurs\": [\"Salut à tous c'est Fanta\"]},{\"code\": \"couleurs\",\"valeurs\": [\"images/sunflower.bmp\",\"29\"]}]";

void Lecture_JSON(int socketfd)
{
  long value;
  char check[1024];
  char temp[1024];
  char mess[11]="\"message\"";
  char coul[11]="\"couleurs\"";
  char valeur_mess[1024];
  char contenu[1024];
  char valeur_coul1[1024];
  char valeur_coul2[1024];
  int ok =0;
  char tempo_coul2[1024];
  while (str){
    memset(valeur_mess,0,sizeof(valeur_mess));
    str = strstr(str, "\"code\"");
    if (str == NULL) {
            break;
        }
    str = strchr(str, ':');
        if (str == NULL) {
            break;
        }
    str++;
    str++;
    memset(check, 0, sizeof(check));
    while (*str != ',') {
            memset(temp,0,sizeof(temp));
            temp[0]=*str;
            strcat(check, temp);
            str++;
        }

    if (strcmp(mess,check)==0){
      strcpy(valeur_mess, "message: ");
      str = strstr(str, "\"valeurs\"");
      str = strchr(str, ':');
      str++;
      str++;
      str++;
      memset(contenu, 0, sizeof(contenu));
      while (*str != ']') {
              memset(temp,0,sizeof(temp));
              temp[0]=*str;
              strcat(contenu, temp);
              str++;
          }
      strcat(valeur_mess,contenu);
      envoie_recois_message(socketfd,valeur_mess);

    }
    if (strcmp(&coul[0],&check[0])==0){
      memset(valeur_coul1,0,sizeof(valeur_coul1));
      memset(valeur_coul2,0,sizeof(valeur_coul2));
      str = strstr(str, "\"valeurs\"");
      str = strchr(str, ':');
      str++;
      str++;
      str++;
      
      while(*str!=']') {
        memset(contenu, 0, sizeof(contenu));
        while((*str!=',') && (*str != ']') ){
              memset(temp,0,sizeof(temp));
              temp[0]=*str;
              strcat(contenu, temp);
              str++;
          }
        if (ok==0){
          strcat(valeur_coul1,contenu);
          str++;
          ok+=1;
        }
        else{
          strcat(valeur_coul2,contenu);  
        }
      }
      printf("ar1 %c, ar2 %s\n",valeur_coul2[1],valeur_coul1);
      int nmb = atoi(&valeur_coul2[1]);
      printf("nmb : %d\n",nmb);
      if (nmb<31){
        printf("ar2 %s, ar1 %s\n",valeur_coul2,valeur_coul1);
        memmove(valeur_coul1, valeur_coul1+1, strlen(valeur_coul1)-2);
        valeur_coul1[strlen(valeur_coul1)-2]='\0';
        //valeur_coul1[strlen(valeur_coul1)-1]="\0";
        //memset(valeur_coul1,0,1);
        printf("tempo2 : %s\n",valeur_coul1);
        //printf("tempo2 : %s\n",valeur_coul1+1);
        envoie_couleurs(socketfd,valeur_coul1,valeur_coul2);
    }
    
  }
}
}

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(int socketfd,char *valeur_mess)
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));


  // Demandez à l'utilisateur d'entrer un message
  
  strcat(data, valeur_mess);

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

void analyse(char *pathname, char *data, int nmb_int, char *nmb)
{
  // compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  strcpy(data, "couleurs: ");
  char temp_string[10] = "10" ;
  if (cc->size < 10)
  {
    sprintf(temp_string, "%d,", cc->size);
  }
  char tempo[10];
  memset(tempo,'0',strlen(tempo));
  sprintf(tempo,"%d",nmb_int);
  strcat(data,tempo);
  strcat(data,",");

  // choisir 10 couleurs
  for (count = 1; count < nmb_int+1 && cc->size - count > 0; count++)
  {
    if (cc->compte_bit == BITS32)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc24[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    if (cc->compte_bit == BITS24)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc32[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    strcat(data, temp_string);
  }

  // enlever le dernier virgule
  data[strlen(data) - 1] = '\0';
}

int envoie_couleurs(int socketfd, char *pathname, char * nmb)
{
  char data[1024];
  memset(data, 0, sizeof(data));
  int nmb2 = atoi(nmb);
  printf("pathname : %s\n",pathname);
  analyse(pathname, data, nmb2, nmb);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}

int main()
{
  int socketfd;

  struct sockaddr_in server_addr;

  // if (argc < 2)
  // {
  //   printf("usage: ./client chemin_bmp_image\n");
  //   return (EXIT_FAILURE);
  // }

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
  Lecture_JSON(socketfd);
    // envoyer et recevoir un message
    
  // else
  // {
  //   // envoyer et recevoir les couleurs prédominantes
  //   // d'une image au format BMP (argv[1])
  //   int nmb = atoi(argv[2]);
  //   if (nmb<31){
  //   envoie_couleurs(socketfd, argv[1],argv[2]);
  //   }
  //   else{
  //     printf("Nombre de couleur trop grand\n");
  //   }
  

  close(socketfd);
}

