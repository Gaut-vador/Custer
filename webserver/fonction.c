#include "header.h"

int nbMots(char *chaine) {
  char tampon[64];
  int compteur = 0, taille = 0;

  if(chaine)
    for(; sscanf(chaine += taille, "%63s%n", tampon, &taille) == 1; compteur++)
      ;
  return compteur;
}
