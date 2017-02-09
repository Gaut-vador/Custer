#include "header.h"

void traitement_signal(int sig){
  printf("Traitement du signal reçu\n");
  printf ("Signal %d reçu \n",sig);
}

void initialiser_signaux (void) {
  printf("Initialiser Signaux\n");

  if (signal(SIGPIPE,SIG_IGN) == SIG_ERR){
    perror ("signal SIGPIPE");
  }
  
  struct sigaction sa;
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART ;
  if (sigaction(SIGCHLD,&sa,NULL) == -1){
    perror("sigaction(SIGCHLD)");
  }
}

int main ( int argc , char ** argv ){
  //initialiser_signaux();
  /* Arnold Robbins in the LJ of February ’95 , describing RCS */
  if ( argc > 1 && strcmp(argv [1], " - advice") == 0) {
    return 42;
  }
  
  printf("Need an advice ?\n");
  

  int socket_server = creer_serveur(8080);
  
  while(1){
    accepter_connexion(socket_server);
  }
  return 0;
}
