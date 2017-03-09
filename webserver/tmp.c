#include "header.h"

int verif_protocole(char* prot){
	if(prot[0] == 'H' && prot[1] == 'T' && prot[2] == 'T' && prot[3] == 'P' && prot[4] == '/' && prot[5] == '1' && (prot[6] == '1' || prot[6] == '0'))
		return 1;
	else
		return -1;
}
