#include "header.h"

int nbMots(char *chaine) {
  char tampon[64];
  int compteur = 0, taille = 0;

  if(chaine)
    for(; sscanf(chaine += taille, "%63s%n", tampon, &taille) == 1; compteur++)
      ;
  return compteur;
}

char *mots(char *str,int idx) {
  char *chaine = str;
  char *stRez = malloc(sizeof(char)*50);
  int cpt = 0;
  int stCpt = 0;
  int i;
  
  for(i=0;chaine[i]!='\0';i++) {
    while(chaine[i] == ' ' && chaine[i+1] == ' ')
      i++;
    if(chaine[i]!=' ' && chaine[i] != '\n') {
      stRez[stCpt ++] = chaine[i];
    }else {
      stCpt = 0;
      if(cpt ++ == idx)
	return stRez;
      memset(stRez,0,sizeof(stRez));
    }
  }
  return NULL;
}

int verif_protocole(char* prot){
  if(strcmp(prot, "HTTP/1.1") == 0 || strcmp(prot, "HTTP/1.0") == 0 )
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

char *okMessage(int id,const char* str) {
  printf("okMessage");
  char *entete = "HTTP/1.1 200 OK\r\nContent-Length: ";
  char c = strlen(str)+'0';
  //entete[strlen(entete)] = c;
  //entete[strlen(entete)] = '\0';
  /*char *rez = malloc(sizeof(str) + sizeof(entete) + sizeof(char)*6);
  printf("malloc ok");
  int cpt = 0 ;
  while(entete[cpt++] != '\0') {
    printf("cpt : %d",cpt);
  }
  entete[cpt++] = strlen(str);
  entete[cpt] = '\0';*/
  return entete;
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
