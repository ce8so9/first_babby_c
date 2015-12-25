#ifndef _REPERTOIRE_H
#define _REPERTOIRE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _date {
  unsigned char jour;
  unsigned char mois;
  unsigned short annee;
} Date;

typedef struct _adresse {
  char rue[50];
  int code_postal;
  char ville[25];
} Adresse;

typedef struct _contact {
  char nom[30];
  char prenom[30];
  Date date_naissance;
  char telephone[20];
  Adresse adresse;
} Contact;

void set_nom_prenom(Contact *c, char *nom, char *prenom);
void set_date(Contact *c, unsigned char jour, unsigned char mois, unsigned short annee);
void set_adresse(Contact *c, char *rue, unsigned int code_postal, char *ville);
void set_telephone(Contact *c, char *tel);
Contact *nouveau_contact(void);
void liberer_contact(Contact *c);
Contact *cree_repertoire(int n);
Contact *resize_repertoire(Contact *c, unsigned int n2);
void ecrire(Contact *r, unsigned int n, char *nom_fichier);
void lire(char *nom_fichier, Contact *r, unsigned int *n);
void afficher_contact(const Contact *c);
Contact *ajouter(Contact *rep, unsigned int *n, Contact *c);
void rechercher_nom(Contact *r, unsigned int n, char *nom);
void rechercher_ne_avant(Contact *r, unsigned int n, Date d);
void rechercher_ne_avant2(Contact *r, unsigned int n, Date d, Contact **res, unsigned int *n_res);

#endif
