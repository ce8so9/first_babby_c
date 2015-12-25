#include "repertoire.h"

void set_nom_prenom(Contact *c, char *nom, char *prenom)
{
  unsigned int i;
  for (i = 0; i < strlen(nom); i++) {
    c->nom[i] = nom[i];
  }
   for (i = 0; i < strlen(prenom); i++) {
    c->prenom[i] = prenom[i];
  }
}

void set_date(Contact *c, unsigned char jour, unsigned char mois, unsigned short annee)
{
  c->date_naissance.jour = jour;
  c->date_naissance.mois = mois;
  c->date_naissance.annee = annee;
}

void set_adresse(Contact *c, char *rue, unsigned int code_postal, char *ville)
{
  unsigned int i;
  for (i = 0; i < strlen(rue); i++) {
    c->adresse.rue[i] = rue[i];
  }
   for (i = 0; i < strlen(ville); i++) {
    c->adresse.ville[i] = ville[i];
  }

  c->adresse.code_postal = code_postal;
}
 
void set_telephone(Contact *c, char *tel)
{
  unsigned int i;
  for (i = 0; i < strlen(tel); i++) 
    c->telephone[i] = tel[i];  
}

Contact *nouveau_contact(void)
{
	Contact *nc = (Contact *) malloc(sizeof(Contact)*1);
   
  nc->nom[0] = '\0';
  nc->prenom[0] = '\0';

	nc->date_naissance.jour = 0;
	nc->date_naissance.mois = 0;
	nc->date_naissance.annee = 0;

  nc->telephone[0] = '\0';

  nc->adresse.rue[0] = '\0';
	nc->adresse.code_postal = 0;
  nc->adresse.ville[0] = '\0';

	return nc;
}

void liberer_contact(Contact *c){
    free(c);
}

Contact *cree_repertoire(int n)
{
	Contact *r = (Contact *)malloc(sizeof(Contact)*n);
	unsigned int i;
	for (i = 0; i < n; i++) {
		r[i].nom[0] = '\0';
		r[i].prenom[0] = '\0';
		r[i].date_naissance.jour = 0;
		r[i].date_naissance.mois = 0;
		r[i].date_naissance.annee = 0;
		r[i].telephone[0] = '\0';
		r[i].adresse.rue[0] = '\0';
		r[i].adresse.code_postal = 0;
		r[i].adresse.ville[0] = '\0';
	}
	return r;
}

Contact *resize_repertoire(Contact *c, unsigned int n2) 
{
	Contact *c2 = (Contact *)realloc(c, n2*sizeof(Contact));
	if (c2 == NULL) {
		printf("Probleme d'allocation\n");
		return NULL;
	}
	return c2;
}

void ecrire(Contact *r, unsigned int n, char *nom_fichier)
{
	FILE *f = fopen(nom_fichier,"wb");
	if (f == NULL) {
	  printf("Impossible d'ouvrir le fichier %s \n",nom_fichier);
	  return;
	}
	fwrite(r, sizeof(Contact), n, f);
	fclose(f);
}

void lire(char *nom_fichier, Contact *r, unsigned int *n)
{
  Contact clu;
  r = cree_repertoire(1);
  FILE *f = fopen(nom_fichier, "rb");
  if (f == NULL)  {
    printf("Impossible d'ouvrir le fichier %s \n",nom_fichier);
    return;
  }
  unsigned int i = 0;
  *n = 1;
  unsigned int nblu = fread(&clu, sizeof(Contact), 1, f);
  if (nblu == 1) {
    r[i] = clu;
  }
  while(!feof(f)) {
    nblu = fread(&clu,sizeof(Contact), 1,f);
    if (nblu == 1) {
      (*n)++;
      i++;
      r = resize_repertoire(r,*n);
      r[i] = clu;
    }
  }
  fclose(f);
}

void afficher_contact(const Contact *c)
{
  if (c == NULL) {return;}
  printf("Nom: %s \t\t prenom: %s\n",c->nom, c->prenom);
  printf("Date de naissance: %d/%d/%d\n",c->date_naissance.jour,c->date_naissance.mois, c->date_naissance.annee);
  printf("Telephone: %s\n",c->telephone); 
  printf("Adresse: %s %d %s\n",c->adresse.rue,c->adresse.code_postal, c->adresse.ville);
}

void rechercher_nom(Contact *r, unsigned int n, char *nom)
{
  int i = 0;

  for (; i < n; i++) {
    if (strcmp(r[i].nom, nom) == 0)
      afficher_contact(r+i);
  }
}

void rechercher_ne_avant(Contact *r, unsigned int n, Date d)
{
  int i = 0;

  for (; i < n; i++) {
    if ((r+i)->date_naissance.annee < d.annee) {
      afficher_contact(r+i);
      continue;
    } else if ((r+i)->date_naissance.mois < d.mois) {
      afficher_contact(r+i);
      continue;
    } else if ((r+i)->date_naissance.jour < d.jour) {
      afficher_contact(r+i);
      continue;
    } else {}
  }
}

Contact *ajouter(Contact *rep, unsigned int *n, Contact *c)
{
  Contact *nr = NULL;

  if (rep == NULL)
    rep = cree_repertoire(1);
  else 
    nr = realloc(rep, ((*n)*sizeof(Contact) + 1));

  set_nom_prenom(nr+(*n)+1, c->nom, c->prenom);
  set_adresse(nr+(*n)+1, c->adresse.rue, c->adresse.code_postal, c->adresse.ville);
  set_telephone(nr+(*n)+1, c->telephone);
  set_date(nr+(*n)+1, c->date_naissance.jour, c->date_naissance.mois, c->date_naissance.annee);

  return nr;
}

void rechercher_ne_avant2(Contact *r, unsigned int n, Date d, Contact **res, unsigned int *n_res)
{
  int i = 0;
  *n_res = 0;

  for (; i < n; i++) {
    if ((r+i)->date_naissance.annee < d.annee) {
      ajouter(*res, n_res, (r+i));
      (*n_res)++;
      continue;
    } else if ((r+i)->date_naissance.mois < d.mois) {
      ajouter(*res, n_res, (r+i));
      (*n_res)++;
      continue;
    } else if ((r+i)->date_naissance.jour < d.jour) {
      ajouter(*res, n_res, (r+i));
      (*n_res)++;
      continue;
    } else {}
  }

}
