#ifndef __SOCKET_H__
#define __SOCKET_H__
	/** Cree une socket serveur qui ecoute sur toute les interfaces IPv4
	de la machine sur le port passe en parametre . La socket retournee
	doit pouvoir etre utilisee directement par un appel à accept .
	La fonction retourne -1 en cas d ’ erreur ou le descripteur de la
	socket creee . */
int creer_serveur (int port);
# endif

void accepter_connexion(int socket_serveur);