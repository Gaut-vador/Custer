#include "header.h"

int nbMots(char *chaine) {
  char tampon[64];
  int compteur = 0, taille = 0;

  if(chaine)
    for(; sscanf(chaine += taille, "%63s%n", tampon, &taille) == 1; compteur++){
    }
  return compteur;
}

char *mots(char *str,int idx) {
  char *mot1 = malloc(sizeof(char)*50);
  char *mot2 = malloc(sizeof(char)*50);
  char *mot3 = malloc(sizeof(char)*50);
  sscanf(str,"%s %s %s",mot1,mot2,mot3);
  if(idx == 0)
    return mot1;
  else if(idx == 1)
    return mot2;
  else if(idx == 2)
    return mot3;
  return mot3;
}


int verif_protocole(char* prot){
  if(strcmp(prot, "HTTP/1.1") || strcmp(prot, "HTTP/1.0"))
    return 1;
  else
    return -1;
}

int verifEmptyStr(char *str) {
  if((strlen(str) == 1 && str[0] == '\n') || (strlen(str) == 2 && str[0] == '\r' && str[1] == '\n'))
    return 1;
  return -1;
}

char *errorMessage(int id) {
  if(id == 400) {
    return "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
  }
  return NULL;
}

char *okMessage(int id) {
  return "HTTP/1.1 200 OK\r\nContent-Length: ";
}

int enoughSpaces(char *recu,int size, FILE *discript_socket) {
  int cptEmpty = 0;
  while(fgets(recu, size, discript_socket) != NULL && cptEmpty == 2 ) {
    fprintf(discript_socket, "nombre de \n%d", cptEmpty);
    if(verifEmptyStr(recu))
      cptEmpty++;
    if(!verifEmptyStr(recu))
      cptEmpty = 0;
  }
  if(cptEmpty == 2)
    return 1;
  return 0;
}
