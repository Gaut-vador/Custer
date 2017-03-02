#include "header.h"

pid_t pid;

void traitement_signal(int sig){
  printf("Traitement du signal %d reçu\n",sig);
  waitpid(pid,&sig,WNOHANG); 
}

void initialiser_signaux (void) {
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
  printf("Loading Cavalry ... ");
  
  int fd  = open("../data/custer.ascii",O_RDONLY);

  if(fd = -1)
    perror("open custer.ascii");
  
  char *message_bienvenue = malloc(3000*sizeof(char));
  read(fd,message_bienvenue,3000*sizeof(char));
  close(fd);
  
  initialiser_signaux();

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
      FILE * discript_socket = fdopen(socket_client ,"w+");
      
      if(socket_client==-1){
	perror("Erreur lors de la connection du client");
	return 0;
      }
      
      if((pid = fork()) == -1) {
	perror("Erreur lors de la création du processus fils");
      }else if(pid==0){
	fprintf(discript_socket,message_bienvenue);
	
	char recu[50];
	char prompt[] = "Custer yelling at you :";
	
	while(socket_client){
	  fgets(recu,50,discript_socket);
	  strcat(prompt,recu);
	  fprintf(discript_socket,prompt);
	}
      }
    }
  }	
}
