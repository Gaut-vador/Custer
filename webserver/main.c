#include "header.h"

pid_t pid;

void traitement_signal(int sig){
  printf("Traitement du signal %d reçu\n",sig);
  waitpid(pid,&sig,WNOHANG);
}

void initialiser_signaux (void) {
  printf("Initialisation of smoke signal ... ");
  if(signal(SIGPIPE,SIG_IGN) == SIG_ERR){
    perror ( "Erreur lors de l'initialisation des signaux" );
  }
  
  struct sigaction sa;
  
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD,&sa,NULL)==-1){
    perror("sigaction(SIGCHLD)");
  }
}


int main(int argc, char ** argv){
  initialiser_signaux();
  printf("Loading Cavalry ... ");
  
  const char * message_bienvenue = "\n\nBonjour, bienvenue sur le serveur Custer!\nSur ce serveur nous ne traitons pas nos clients comme des Apaches!\nGeorge Armstrong Custer est un général de cavalerie américain\n(5 décembre 1839 New Rumley, Ohio - 25 juin 1876, Montana).\n\nIl est célèbre pour ses exploits durant la guerre de Sécession et sa défaite lors de la bataille de Little Bighorn face à une coalition de tribus indiennes.\nIl est une des principales figures américaines des guerres indiennes du xixe siècle.\r\n";
  
  int socket_server=creer_serveur(8080);
  if(socket_server == -1 ){
    printf("Apaches won !\n");
    return 0;
  }
  else {
    printf("Let's make America great !\n");
    int socket_client;
    while(1){
      socket_client=accept(socket_server, NULL, NULL);
      if(socket_client==-1){
	perror("Erreur lors de la connection du client");
	return 0;
      }
      FILE * discript_socket = fdopen(socket_client, "w+");
      if((pid = fork()) == -1) {
	perror("Erreur lors de la création du processus fils");
      }else if(pid==0){
	int size = 1024;
	char recu[size];
	char prompt[] = "<Custer>";
	while(fgets(recu, size, discript_socket) != NULL){
	  if(nbMots(recu) == 3) {
	    if(strcmp(mots(recu,0), "GET") == 0 && verif_protocole(mots(recu,2))) {
	      enoughSpaces(recu,size,discript_socket);
	      fprintf(discript_socket, "%s%d\r\n%s",okMessage(200),(int)strlen(message_bienvenue),message_bienvenue);
	    }else {
	      enoughSpaces(recu,size,discript_socket);
	      fprintf(discript_socket, "%s", errorMessage(400));
	    }
	  }else {
	    enoughSpaces(recu,size,discript_socket);
	    fprintf(discript_socket, "%s", errorMessage(400));
	  }
	}
	close(socket_client);
	return 0;
      }
    }
  }	
}
