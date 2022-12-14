/*
* Nom de fichier : client.c
* Objectifs : - Exercice 5.4 : Permettre à l'utilisateur d'envoyer un message au serveur et de répondre sur celui ci
*             - Exercice 5.5 : Permettre à l'utilisateur d'envoyer un calcul au serveur et obtenir la réponse du calcul sur client
              - Exercice 5.6 : Calculer la moyenne de chaque élève et la moyenne de la classe à partir de fichiers
* Auteurs : Evann Nalewajek , Gaëlle Leroux
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
  char code[10];
  char reponse[1024];
  memset(reponse,'0',1024);

  

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
  if (strcmp(&data[9],&fin[0])==3){ // Si le serveur a reçu "fin" cela veut dire qu'il doit sortir de la boucle
    printf("Fin de journée pour moi \n");
    break;
  }

  memset(code,'0',10);
  sscanf(data, "%s:", code);
  
  // Si le message commence par le mot: 'message:'
  if (strcmp(code, "message:") == 0){
    // on remplit data avec la réponse de l'utilisateur et on la renvoie au client
    printf("Votre réponse (max 1000 caracteres): ");
    fgets(reponse, sizeof(reponse), stdin);
    strcpy(data, "message: ");
    strcat(data, reponse);
    renvoie_message(client_socket_fd, data);
  }

  // Si le message commence par le mot: 'calcul:'
  if(strcmp(code,"calcul:")==0){
    int ok = 0;
    int i = 8;
    char op;
    char espace[1]=" ";
    float nmb1;
    float nmb2;
    for (int j=0;(i+j)<strlen(data);j++){ // On lit le message data
      void *ptr = &data[i+j];
      void *pespace = &espace[0];
      if (*((char*)ptr)!=*((char*)pespace)){ // Si le caractère de date est différent d'un espace
        if (ok==0){ // Si ok vaut 0 cela veut dire que nous somme sur l'opérateur
          op = data[i+j];
          ok+=1;
          continue;
        }
        if (ok==1){ // Si ok vaut 1 cela veut dire que nous somme sur le premier nombre
          nmb1 = atof(&data[i+j]); // on le transforme en float
          ok+=1;
          int t =1;
          while(*((char*)ptr+t)!=*((char*)pespace)){ // on avance le pointeur de la taille du nombre qu'on vient de transformer en float
            t+=1;
            j+=1;
          }
          continue;
        }
        if (ok==2){ // Si ok vaut 2 cela veut dire que nous somme sur le deuxième nombre
          nmb2 = atof(&data[i+j]);
          ok+=1;
        }
      }
      }

    
    char code[10];
    sscanf(data, "%s:", code);

    memset(data,'0',1024);
    strcpy(data, "calcul: ");

    float tempo =0;
    int j=1;
    int m = 0;
    char message[1024];

    if (ok==3){ // Si ok vaut 3 cela veut dire que la commande rentré par l'utilisateur est valide
      switch (op){ // on switch sur l'opération voulue
        case '+' :
        tempo = nmb1 + nmb2; // on fait l'opération
        sprintf(message,"%f",tempo); // on le transforme en char
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
        sprintf(message,"%f",tempo);
        j = 1;
        while(tempo/10>0){
            tempo = tempo/10;
            j+=1;
          }
        m+=1;
        break;

        case '%' :
        tempo = (int)nmb1 % (int)nmb2;
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

    char message2[19] = "Entrée non valide"; 

    void *pmes =&message[0];
    *((char*)pmes+j)='\0';

    if (m==1){
    strcat(data, message); // envoie la réponse du calcul au client
    }
    else{ // Si m!=1 cela veut dire que la commande rentré par l'utilisateur n'est pas valide
      strcat(data, message2); // on renvoie donc au client "Entrée non valide"
    }
    strcat(data,"\0");
    renvoie_message(client_socket_fd, data);
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