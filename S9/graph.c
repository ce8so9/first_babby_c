#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "abr.h"
#include "liste.h"

static int node_id = 0;

int dumptree_aux(FILE *stream, Un_nabr *abr) {
  int id = node_id++;
  
  if (abr == NULL)
    fprintf(stream, "n%i [shape=point];\n", id);

  else {
    fprintf(stream, "n%i [label=\"%s\"];\n", id, abr->truc->data.sta.nom);
    fprintf(stream, "n%i -> n%i;\n", id, dumptree_aux(stream, abr->g));
    fprintf(stream, "n%i -> n%i;\n", id, dumptree_aux(stream, abr->d));
  }

  return id;
}

void dumptree(FILE *stream, Un_nabr *abr)
{
  node_id = 0;
  fprintf(stream, "digraph tree {\n");
  dumptree_aux(stream, abr);
  fprintf(stream, "}\n");
}

int main(int argc, char *argv[])
{

    FILE *dumpfile = NULL;
	Un_elem *liste_sta = NULL, *l;
	Un_nabr *abr;
	Une_coord no, se;

	if (argc != 3) {
		fprintf(stderr, "Usage : treedump fichier_stations tree_file\n");
		return EXIT_FAILURE;
	}
	
	if ((liste_sta = lire_stations(argv[1])) == NULL) {
		fprintf(stderr, "Erreur : Lecture fichier stations\n");
		return EXIT_FAILURE;
	}
	
	limites_zone(liste_sta, &no, &se);

	printf("Stations dans [%f,%f] et [%f,%f]\n", no.lon, no.lat, se.lon, se.lat);

	//ecrire_liste(stdout, liste_sta);

	abr = construire_abr(liste_sta);

	for (l=liste_sta; l; l=l->suiv)
		if (chercher_station(abr, l->truc->data.sta.nom) == NULL)
			fprintf(stderr, "Station non trouvee!!!\n");

    if ((dumpfile = fopen(argv[2], "w")) == NULL) {
        int errsv = errno;
        fprintf(stderr, "Impossible d'ecrire dans le fichier!\n");
        fprintf(stderr, "ERRNO: %s\n", strerror(errsv));
        exit(EXIT_FAILURE);
    }

    dumptree(dumpfile, abr);

    fclose(dumpfile);

    detruire_abr(abr);
    detruire_liste_et_truc(liste_sta);
}

