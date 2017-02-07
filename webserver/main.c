#include "header.h"

void initialiser_signaux (void) {
  if ( signal ( SIGPIPE , SIG_IGN ) == SIG_ERR )
    {
      perror ( " signal " );
    }
}

int main ( int argc , char ** argv ){
  initialiser_signaux();
  /* Arnold Robbins in the LJ of February ’95 , describing RCS */
  if ( argc > 1 && strcmp(argv [1], " - advice") == 0) {
    printf ("Don’t Panic !\n");
    return 42;
  }
  
  printf("Need an advice ?\n");
  

  int socket_server = creer_serveur(8080);
  
  while(1){
    accepter_connexion(socket_server);
  }
  return 0;
}
