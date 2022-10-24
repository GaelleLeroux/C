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
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
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
  char fin[4]="fin";

  while(1){
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
  if ((&data[1]==&fin[1])&&(&data[2]==&fin[2])&&(&data[3]==&fin[3])){
    printf("Je pars en week-end");
    break;
  }
  int ok = 0;
  int i = 8;
  char op;
  char espace[1]=" ";
  int nmb1;
  int nmb2;
  for (int j=0;(i+j)<strlen(data);j++){
    void *ptr = &data[i+j];
    void *pespace = &espace[0];
    if (*((char*)ptr)!=*((char*)pespace)){
      if (ok==0){
        op = data[i+j];
        ok+=1;
        continue;
      }
      if (ok==1){
        nmb1 = atoi(&data[i+j]);
        ok+=1;
        int tempo = nmb1;
        while(tempo/10>0){
          tempo = tempo/10;
          j+=1;
        }
        continue;
      }
      if (ok==2){
        nmb2 = atoi(&data[i+j]);
        int nmb3 = atoi(&data[i+j-1]);
        printf("nmb3 : %d\n",atoi(&data[i+j-3]));
        printf("nmb3 : %d\n",atoi(&data[i+j-2]));
        printf("nmb3 : %d\n",atoi(&data[i+j-1]));
        printf("nmb3 : %d\n",atoi(&data[i+j]));
        printf("nmb3 : %d\n",atoi(&data[i+j+1]));
        printf("nmb3 : %d\n",atoi(&data[i+j+2]));
        printf("Message recu: %s\n", data);
        ok+=1;
      }
    }
    }

  
  char code[10];
  sscanf(data, "%s:", code);


  strcpy(data, "calcul: ");

  float tempo =0;
  int j=1;
  int m = 0;
  char message[1024];

  if (ok==3){
    switch (op){
      case '+' :
      tempo = nmb1 + nmb2;
      printf("tempo : %f nmb1 : %i nmb2 : %i \n",tempo,nmb1,nmb2);
      sprintf(message,"%f",tempo);
      j = 1;
      while(tempo/10>0){
          tempo = tempo/10;
          j+=1;
        }
      m+=1;
      break;

      case '-' :
      tempo = nmb1 - nmb2;
      sprintf(message,"%f",tempo);
      j = 1;
      while(tempo/10>0){
          tempo = tempo/10;
          j+=1;
        }
      m+=1;
      break;

      case '*' :
      tempo = nmb1 * nmb2;
      sprintf(message,"%f",tempo);
      j = 1;
      while(tempo/10>0){
          tempo = tempo/10;
          j+=1;
        }
      m+=1;
      break;

      case '/' :
      tempo = (float)nmb1 / nmb2;
      printf("tempo : %f\n",tempo);
      sprintf(message,"%f",tempo);
      j = 1;
      while(tempo/10>0){
          tempo = tempo/10;
          j+=1;
        }
      m+=1;
      break;

      case '%' :
      tempo = nmb1 % nmb2;
      printf("tempo : %f\n",tempo);
      sprintf(message,"%f",tempo);
      j = 1;
      while(tempo/10>0){
          tempo = tempo/10;
          j+=1;
        }
      m+=1;
      break;
    }
    
  }

  char message2[15] = "Mauvais calcul";

  void *pmes =&message[0];
  *((char*)pmes+j)='\0';

  if (m==1){
  strcat(data, message);
  }
  else{
    strcat(data, message2);
  }
  
  renvoie_message(client_socket_fd, data);
  

  
  
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
