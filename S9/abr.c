#include "abr.h"
#include <assert.h>

#define MAX(x,y) ((x) < (y) ? (y) : (x))

Un_nabr *creer_nabr(Un_truc *truc) {
  assert(truc != NULL);
  Un_nabr *abr = (Un_nabr *)malloc(sizeof(Un_nabr));

  abr->truc = truc;
  abr->height = 1;
  abr->g = NULL;
  abr->d = NULL;

  return abr;
}


unsigned int height(Un_nabr *abr) {
  if (abr == NULL) return 0;
  //assert(abr->height == (MAX(height(abr->g), height(abr->d)) +1));
  return abr->height;
}

int balance(Un_nabr *abr) {
  if(abr == NULL) return 0;
  return height(abr->g) - height(abr->d);
}

Un_nabr *left_rotate(Un_nabr *abr) {
  assert(abr    != NULL);
  assert(abr->d != NULL);

  Un_nabr *d = abr->d;
  abr->d = d->g;
  d->g   = abr;

  //Optimizable
  abr->height = MAX(height(abr->g), height(abr->d)) +1;
  d->height = MAX(height(d->g), height(d->d)) +1;
  
  return d;
}

Un_nabr *right_rotate(Un_nabr *abr) {
  assert(abr    != NULL);
  assert(abr->g != NULL);

  Un_nabr *g = abr->g;
  abr->g = g->d;
  g->d   = abr;

  //Optimizable
  abr->height = MAX(height(abr->g), height(abr->d)) +1;
  g->height = MAX(height(g->g), height(g->d)) +1;
  
  return g;
}

Un_nabr *inserer_elem(Un_nabr *abr, Un_nabr *elem) {
  assert(elem != NULL);

  if (abr == NULL) return elem;

  int flag = strcmp(elem->truc->data.sta.nom, abr->truc->data.sta.nom);

  if (flag > 0)
    abr->d      = inserer_elem(abr->d, elem);
  else if (flag == 0)
    fprintf(stderr, "abr.c: Adding existing element '%s'\n", elem->truc->data.sta.nom);
  else
    abr->g      = inserer_elem(abr->g, elem);

  abr->height = MAX(height(abr->g), height(abr->d)) +1;

  int bal = balance(abr);
  if (bal == -2) {
    int bal_d = balance(abr->d);

    if(bal_d == -1)
      abr = left_rotate(abr);
    else if (bal_d == 0)
      fprintf(stderr, "Right rebalancing at 0\n");
    else {
      abr->d = right_rotate(abr->d);
      abr    = left_rotate(abr);
    }
  } else if (bal == 2) {
    int bal_g = balance(abr->g);

    if(bal_g == 1)
      abr = right_rotate(abr);
    else if (bal_g == 0)
      fprintf(stderr, "Left rebalancing at 0\n");
    else {
      abr->g = left_rotate(abr->g);
      abr    = right_rotate(abr);
    }
  }

  return abr;
}

Un_nabr *construire_abr(Un_elem *liste_sta) {
  Un_nabr *n = NULL;
  Un_nabr *a = NULL;

  while (liste_sta != NULL) {
    n = creer_nabr(liste_sta->truc);
    a = inserer_elem(a, n);
    liste_sta = liste_sta->suiv;
  }

  return a;
}

void detruire_abr(Un_nabr *abr) {
  if (abr == NULL) return;
  Un_nabr *d = abr->d;

  detruire_abr(abr->g);
  free(abr);
  detruire_abr(d);
}

Un_truc *chercher_station(Un_nabr *abr, char *nom)
{
  Un_nabr *curr = NULL;
  int flag = 0;

  curr = abr;

  while (curr != NULL) {

    flag = strcmp(nom, curr->truc->data.sta.nom);

    if (flag == 0)
      return curr->truc;
    else if (flag < 0)
      curr = curr->g;
    else
      curr = curr->d;
  }

  return NULL;
}
