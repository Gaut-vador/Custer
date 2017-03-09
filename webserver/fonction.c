#include "header.h"

int nbMots(char *chaine) {
  char tampon[64];
  int compteur = 0, taille = 0;

  if(chaine)
    for(; sscanf(chaine += taille, "%63s%n", tampon, &taille) == 1; compteur++)
      ;
  return compteur;
}

char** mots(char *str) {
  char *chaine = str;
  char *stRez = malloc(sizeof(char)*50);
  char **rez = malloc(sizeof(stRez)*10);
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
      rez[cpt++] = stRez;
      printf("%s",stRez);
      memset(stRez,0,sizeof(stRez));
      printf("\n");
    }
  }
  return rez;
}
