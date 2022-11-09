/*
* Nom de fichier : serveur.c
* Objectifs : Selon les données reçues de la part du client :
*             - Réaliser un opération avec partir d'un opérande et de deux nombres.
*             - Renvoyer un message reçu.
*             - Extraire d'une image les couleurs prédominantes.
*             Dans les trois cas, le résultat obtenu doit être stocké dans une chaîne de caractère
*             simulant un fichier JSON.
* Auteurs : Evann Nalewajek , Gaëlle Leroux
*/

/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"


void plot(char *data)
{

  // Extraire le compteur et les couleurs RGB
  FILE *p = fopen("gnuplot -persist", "w");
  printf("Plot\n");
  int count = 0;
  int n;
  char *saveptr = NULL;
  char *str = data;
  fprintf(p, "set xrange [-15:15]\n");
  fprintf(p, "set yrange [-15:15]\n");
  fprintf(p, "set style fill transparent solid 0.9 noborder\n");
  fprintf(p, "set title 'Top 10 colors'\n");
  fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
  while (1)
  {
    char *token = strtok_r(str, ",", &saveptr);
    if (token == NULL)
    {
      break;
    }
    str = NULL;
    printf("%d: %s\n", count, token);
    if (count == 1)
    {
      n = atoi(token);
      printf("n = %d\n", n);
    }
    else
    {
      // Le numéro 36, parceque 360° (cercle) / 10 couleurs = 36
      fprintf(p, "0 0 10 %d %d 0x%s\n", (count - 1) * 36, count * 36, token + 1);
    }
    count++;
  }
  fprintf(p, "e\n");
  printf("Plot: FIN\n");
  fclose(p);
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. Ensuite, le serveur envoie un message
 * en retour.
 */
int recois_envoie_message(int socketfd)
{
  struct sockaddr_in client_addr;
  char data[1024];

  unsigned int client_addr_len = sizeof(client_addr);

  // nouvelle connection de client
  int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
  if (client_socket_fd < 0)
  {
    perror("accept");
    return (EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // lecture de données envoyées par un client
  int data_size = read(client_socket_fd, (void *)data, sizeof(data));

  if (data_size < 0)
  {
    perror("erreur lecture");
    return (EXIT_FAILURE);
  }

  /*
   * extraire le code des données envoyées par le client.
   * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
   */
  printf("Message recu: %s\n", data);
  char code[10];
  sscanf(data, "%s", code);
  
  // Sert à convertir le résultat du calcul en chaîne de caractère.
  char solution_calcul_char[1024];

  // check et temp servent à extraire une portion de la chaîne de caractères contenant les données.
  char check[1024];
  char temp[1024];
  // Ces chaînes de caractères vont servir de comparateur, pour que la fonction sache quelle type d'opération il doit faire.
  char mess[11]="\"message\"";
  char coul[11]="\"couleurs\"";
  char cal[9]="\"calcul\"";
  // Création du pointeur qui va naviguer le long de la chaîne de caractères contenant les données.
  char *ptr_data = data;

  while (ptr_data){
    ptr_data = strstr(ptr_data, "\"code\"");
    if (ptr_data == NULL) {
            break;
        }
    ptr_data = strchr(ptr_data, ':');
        if (ptr_data == NULL) {
            break;
        }
    // On avance dans la chaîne de caractères pour arriver à la partie qui nous intéresse.
    ptr_data++;
    ptr_data++;
    memset(check, 0, sizeof(check));

    // On extrait la partie de la chaîne de caractères qui sert à déterminer si l'on souhaite un calcul, un message ou le nombre de couleur.
    while (*ptr_data != ',') {
            memset(temp,0,sizeof(temp));
            temp[0]=*ptr_data;
            strcat(check, temp);
            ptr_data++;
        }

    // Cas où l'on souhaite connaître le nombre de couleurs d'une image.
    if (strcmp(&coul[0],&check[0])==0){
      // nmb_coul permet d'isoler l'information sur le nombre de couleur.
      char nmb_coul[100];
      // Sert à convertir cette information isolée en entier.
      int nmb_coul_int;

      memset(nmb_coul,0,strlen(nmb_coul));
      ptr_data = strstr(ptr_data, "\"valeurs\"");
      ptr_data = strchr(ptr_data, ':');
      ptr_data++;
      ptr_data++;
      ptr_data++;
      ptr_data++;
      temp[0]=*ptr_data;
      ptr_data++;
      temp[1]=*ptr_data;
      strcat(nmb_coul,temp);
      printf("nmb_coul : %s\n",nmb_coul);
      nmb_coul_int = atoi(nmb_coul);
      ptr_data++;
      ptr_data++;
      ptr_data++;
      ptr_data++;

      // Chaque tour de boucle va print une nouvelle couleur, pointée par ptr_data.
      for(int i=1;i<nmb_coul_int+1;i++){
        printf("%d : ",i);
        while(*ptr_data!='\"'){
          printf("%c",*ptr_data);
          ptr_data++;
        }
        printf("\n");
        ptr_data++;
        ptr_data++;
        ptr_data++;
      }
    }

    // Cas où l'on souhaite envoyer un message.
    if (strcmp(mess,check)==0){
      renvoie_message(client_socket_fd, data);
    }

    // Cas où l'on souhaite réaliser un calcul.
    if (strcmp(check,cal)==0){
      ptr_data = strstr(ptr_data, "\"valeurs\"");
      ptr_data = strchr(ptr_data, ':');
      ptr_data++;
      ptr_data++;
      ptr_data++;
      ptr_data++;

      // On extrait l'opérateur dans une chaîne de caractères.
      char op= *ptr_data;
      while(*ptr_data!=','){
      ptr_data++;
      }
      ptr_data++;
      ptr_data++;

      // On extrait le premier nombre dans un float.
      float nmb1 = atof(ptr_data);
      while(*ptr_data!=','){
      ptr_data++;
      }
      ptr_data++;
      ptr_data++;

      // On extrait le deuxième nombre dans un float.
      float nmb2 = atof(ptr_data);
      float sol = 0;
      switch(op){
        case '+' : 
          sol = nmb1+nmb2;
          break;
        case '-':
          sol = nmb1-nmb2;
          break;
        case '%':
          sol = (float)nmb1/nmb2;
          break;
        case '*':
          sol = nmb1*nmb2;
          break;
      }
      // On stock les informations du calcul sous un format JSON.
      memset(data,0,1024);
      strcat(data,"[{\"code\": \"calcul\", \"valeurs\": [\"");
      memset(solution_calcul_char,0,1024);
      sprintf(solution_calcul_char,"%f",sol);
      strcat(data,solution_calcul_char);
      strcat(data,"\"]}]");
      int data_size = write(client_socket_fd, (void *)data, strlen(data));
      if (data_size < 0)
      {
        perror("erreur ecriture");
        return (EXIT_FAILURE);
      }
    }
  }

  // fermer le socket
  close(socketfd);
  return (EXIT_SUCCESS);
}

int main()
{

  int socketfd;
  int bind_status;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Écouter les messages envoyés par le client
  listen(socketfd, 10);

  // Lire et répondre au client
  recois_envoie_message(socketfd);

  return 0;
}
