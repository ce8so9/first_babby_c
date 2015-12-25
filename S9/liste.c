#include "liste.h"
#include "abr.h"
#include "ligne.h"
#include "connexion.h"

#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define R 6371

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc)
{
  Un_elem *nouv_liste = NULL;

  if (liste == NULL) {
    nouv_liste = (Un_elem *) malloc(sizeof(Un_elem));
    nouv_liste->truc = truc;
    nouv_liste->suiv = liste;

    return nouv_liste;
  }

  if (liste->truc->user_val > truc->user_val) {
    nouv_liste = (Un_elem *) malloc(sizeof(Un_elem));
    nouv_liste->truc = truc;
    nouv_liste->suiv = liste;

    return nouv_liste;
  }

  liste->suiv = inserer_liste_trie(liste->suiv, truc);
  return liste;
}

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc)
{
  Un_elem *l = (Un_elem *) malloc(sizeof(Un_elem));

  l->truc = truc;

  if (liste == NULL) {
    l->suiv = NULL;
    return liste;
  }

  l->suiv = liste;

  return l;

}

void ecrire_liste(FILE *flux, Un_elem *liste)
{
  if (liste == NULL) return;

  if (liste->truc->type == STA)
    fprintf(flux, "%s\n", liste->truc->data.sta.nom);

  ecrire_liste(flux, liste->suiv);

}

void detruire_liste(Un_elem *liste)
{
  if (liste == NULL) return;

  Un_elem *curr = liste;

  while (liste != NULL) {
    liste = liste->suiv;
    free(curr);
    curr = liste;
  }

}

void detruire_liste_et_truc(Un_elem *liste)
{
  Un_elem *curr = NULL;
  curr = liste;

  while (curr != NULL) {
    detruire_truc(curr->truc);
    curr = curr->suiv;
  }

  detruire_liste(liste);
}

Un_elem *lire_stations(char *nom_fichier)
{
  FILE *f = NULL;
  char buf[BUFFER_SIZE];
  char c;
  int i, d;
  int state = 0;
  Un_truc *t = NULL;
  Un_elem *l = NULL;
  Tdata data_station;
  Une_coord coord_station;

  data_station.sta.nom = NULL;
  data_station.sta.tab_con = NULL;
  data_station.sta.nb_con = 0;
  data_station.sta.con_pcc = NULL;

  coord_station.lon = 0.0;
  coord_station.lat = 0.0;

  if ((f = fopen(nom_fichier, "r")) == NULL) {
    fprintf(stderr, "Impossible de lire %s\n", nom_fichier);
    return l;
  }   

  while (fgets(buf, BUFFER_SIZE, f)) {

    i = 0;
    d = 0;
    state = 0;

    while ( (c = buf[i]) != '\0') {

      switch (state) {

      case 0:		if (c == ';') {
          state = 1;
          buf[i] = '\0';
          sscanf(buf, "%f", &coord_station.lon);
          d = i + 1;
          break;
        }

      case 1:		if (c == ';') {
          state = 2;
          buf[i] = '\0';
          sscanf(buf+d, "%f", &coord_station.lat);
          d = i + 1;
          break;
        }
      }

      i++;
    }

    if (state != 2) {
      fprintf(stderr, "Erreur concernant le format");
      continue;
    } else 
      data_station.sta.nom = strdup(buf + d);

    data_station.sta.nom[strlen(data_station.sta.nom)-1]='\0'; // Sale
    t = creer_truc(coord_station, STA, data_station, 0);
    l = inserer_liste_trie(l, t);
  }

  fclose(f);
  return l;

}

float deg2rad(float deg) {
  return deg * (M_PI / 180);
}

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta) {

  assert(nom_fichier != NULL);
  FILE *f = fopen(nom_fichier, "r");
  Un_elem* list = NULL;

  char line[BUFFER_SIZE];
  char *ligne = NULL;
  char   *src = NULL;
  char  *dest = NULL;
  Tdata  *cnx = alloca(sizeof(Tdata));

  static Une_coord dummy_coord;
  float cost = 0.0;
  float dlon, dlat, a, c, d, t = 0.0;

  if (f == NULL) {
      fprintf(stderr, "lire_connexions(): Couldn't open file: %s", strerror(errno));
      return NULL;
  }

  while (fgets(line, BUFFER_SIZE, f) != NULL) {
    if (line[0] == '#')  continue; //Skip to next line on comment
    if (line[0] == '\n') continue; //Skip to next line on empty line

    ligne = strtok(line, ";");
    src   = strtok(NULL, ";");
    dest  = strtok(NULL, ";");
    cost  = atof(strtok(NULL, ";"));

    if (strtok(NULL, ";") != NULL) {
      fprintf(stderr, "Erreur concernant le format");
      continue;
    }

    bool well_defined = true;
    Un_truc   *sta_src, *sta_dest;
    Une_ligne *lgn;

    if((sta_src = chercher_station(abr_sta, src)) == NULL) {
      fprintf(stderr, "Source station \"%s\" not found\n", src);
      well_defined = false;
    }

    if((sta_dest = chercher_station(abr_sta, dest)) == NULL) {
      fprintf(stderr, "Destination station \"%s\" not found\n", dest);
      well_defined = false;
    }

    if((lgn = chercher_ligne(liste_ligne, ligne)) == NULL) {
      fprintf(stderr, "Line \"%s\" not found\n", ligne);
      well_defined = false;
    }

    if(!well_defined) {
      fprintf(stderr, "\n");
      continue;
    }

    cnx->con.sta_dep = sta_src;
    cnx->con.sta_arr = sta_dest;
    cnx->con.ligne   = lgn;

    if (cost == 0.0) {
      dlon = deg2rad( fabsf(sta_src->coord.lon - sta_dest->coord.lon) );
      dlat = deg2rad( fabsf(sta_src->coord.lat - sta_dest->coord.lat) );
      a = sinf(dlat/2) * sinf(dlat/2) + cosf(deg2rad(sta_src->coord.lat)) * cosf(deg2rad(sta_dest->coord.lat)) * sinf(dlon/2) * sinf(dlon/2);
      c = 2 * atan2f(sqrtf(a), sqrtf(1-a));
      d = R * c;
      t = (d / lgn->vitesse) * 60 ;
      cost = t;
    }

    Un_elem* hd = malloc(sizeof(Un_elem));
    hd->truc = creer_truc(dummy_coord, CON, *cnx, cost);
    hd->suiv = list;
    list = hd;

  }

  return list;

}

void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se)
{
  float min_lat = liste->truc->coord.lat;
  float min_lon = liste->truc->coord.lon;
  float max_lat = liste->truc->coord.lat;
  float max_lon = liste->truc->coord.lon;

  Un_elem *curr = liste;

  while (curr != NULL) {

    if (curr->truc->type == STA) {
      if (curr->truc->coord.lon < min_lon)
        min_lon = curr->truc->coord.lon;
      else if (curr->truc->coord.lon > max_lon)
        max_lon = curr->truc->coord.lon;

      if (curr->truc->coord.lat < min_lat)
        min_lat = curr->truc->coord.lat;
      else if (curr->truc->coord.lat > max_lat)
        max_lat = curr->truc->coord.lat;
    }

    curr = curr->suiv;
  }

  limite_no->lon = min_lon;
  limite_no->lat = min_lat;
  limite_se->lon = max_lon;
  limite_se->lat = max_lat;

}

Un_truc *extraire_deb_liste(Un_elem **liste)
{
  Un_truc *t = NULL;
  Un_elem *l1, *l2 = NULL;

  l1 = *liste;
  l2 = l1->suiv;
  t = creer_truc(l1->truc->coord, l1->truc->type, l1->truc->data, l1->truc->user_val);

  free(l1->truc);
  l1->suiv = NULL;

  *liste = l2;
  return t;

}

Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc)
{
  Un_elem **l = NULL;
  Un_elem *prev = NULL;
  Un_elem *curr = NULL;
  Un_truc *t = NULL;

  curr = *liste;

  while (curr->truc != truc) {
    prev = curr;
    curr = curr->suiv;
  }

  *l = curr; 
  t = extraire_deb_liste(l);
  prev->suiv = *l;

  *liste = prev;

  return t;
}
