#include "header.h"

void accepter_connexion(int socket_serveur){
  int socket_client ;
  socket_client = accept((socket_serveur), NULL, NULL);

  if (socket_client == -1){
    perror("accept socket_client");
    /* traitement d ’ erreur */
    exit(1); // NE PAS ENLEVER le exit gere le lancement d'un autre serveur sur le meme port
  }
  
  /*On peut maintenant dialoguer avec le client */
  const char * message_bienvenue = "\n\nBonjour, bienvenue sur le serveur Custer!\nSur ce serveur nous le traitons pas nos clients comme des Apaches!\nGeorge Armstrong Custer est un général de cavalerie américain\n(5 décembre 1839 New Rumley, Ohio - 25 juin 1876, Montana).\n\nIl est célèbre pour ses exploits durant la guerre de Sécession et sa défaite lors de la bataille de Little Bighorn face à une coalition de tribus indiennes.\nIl est une des principales figures américaines des guerres indiennes du xixe siècle.\n\n";
  //sleep(1);
  
  pid_t pid = 0;
  if((pid = fork()) == -1)
    perror("fork");
  if(pid != 0) {
    printf("je suis le papa");
      close(socket_client);
  } else {
    write (socket_client, message_bienvenue, strlen(message_bienvenue));

    char message[50];
    while(1){
      sleep(1);
      int length = read(socket_client, message, 50);
      if(length > 0){
	write(socket_client, message, length);
      }
    }
  }
}

int creer_serveur (int port) {  
  //creation de la socket
  int socket_serveur ;
  socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
  if ( socket_serveur == -1){
    perror("socket_serveur");
    return -1;
  }
  
  struct sockaddr_in saddr ;
  
  saddr.sin_family = AF_INET ; /* Socket ipv4 */
  saddr.sin_port = htons(port); /* Port d ’écoute */
  saddr.sin_addr.s_addr = INADDR_ANY ; /* écoute sur toutes les interfaces */

  int optval = 1;
  if ( setsockopt (socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
    perror ( " Can not set SO_REUSEADDR option " );
  
  if ( bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1){
    perror("bind socker_serveur");
    return -1;
  }
  if ( listen ( socket_serveur , 10) == -1){
    perror ( " listen socket_serveur " );
    return -1;
  }
  return socket_serveur;
}
