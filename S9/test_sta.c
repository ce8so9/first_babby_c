#include <stdio.h>

#include "liste.h"
#include "abr.h"

int main(int argc, char *argv[])
	{
	Un_elem *liste_sta = NULL, *l;
	Un_nabr *abr;
	Une_coord no, se;

	if (argc != 2)
		{
		fprintf(stderr, "Usage : test_sta fichier_stations\n");
		return EXIT_FAILURE;
		}
	
	if ((liste_sta = lire_stations(argv[1])) == NULL)
		{
		fprintf(stderr, "Erreur : Lecture fichier stations\n");
		return EXIT_FAILURE;
		}
	
	limites_zone(liste_sta, &no, &se);

	printf("Stations dans [%f,%f] et [%f,%f]\n", no.lon, no.lat, se.lon, se.lat);

	ecrire_liste(stdout, liste_sta);

	abr = construire_abr(liste_sta);

	for(l=liste_sta; l; l=l->suiv)
		if (chercher_station(abr, l->truc->data.sta.nom) == NULL)
			fprintf(stderr, "Station non trouvee!!!\n");
	
	detruire_abr(abr);
	detruire_liste_et_truc(liste_sta);

	return EXIT_SUCCESS;
	}
