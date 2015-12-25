#include<stdio.h>

#include "liste.h"
#include "truc.h"
#include "abr.h"
#include "ligne.h"
#include "aqrtopo.h"

int main(int argc, char *argv[])
	{
	Un_elem *liste_sta = NULL;
	Une_ligne *liste_ligne = NULL;
	Un_elem *liste_con = NULL;
	Un_elem *l;
	Un_nabr *abr_sta;
	Un_noeud *aqr_sta;
	Une_coord limite_no;
	Une_coord limite_se;

	if (argc != 4)
		{
		fprintf(stderr, "Usage : test_aqr fichier_stations fichier_ligne fichier connexion\n");
		return EXIT_FAILURE;
		}
	
	if ((liste_sta = lire_stations(argv[1])) == NULL)
		{
		fprintf(stderr, "Erreur : Lecture fichier stations\n");
		return EXIT_FAILURE;
		}
	
	abr_sta = construire_abr(liste_sta);

	if ((liste_ligne = lire_lignes(argv[2])) == NULL)
		{
		fprintf(stderr, "Erreur : Lecture fichier lignes\n");
		return EXIT_FAILURE;
		}
	
	if ((liste_con = lire_connexions(argv[3], liste_ligne, abr_sta)) == NULL)
		{
		fprintf(stderr, "Erreur : Lecture fichier connexion\n");
		return EXIT_FAILURE;
		}
	
	aqr_sta = construire_aqr(liste_sta);

	//test aqr
	//test rechercher

	for(l = liste_sta; l; l = l->suiv)
		{
		Une_coord coord = l->truc->coord;
		if (chercher_aqr(aqr_sta, coord) != l->truc)
			fprintf(stderr, "Erreur : Station %s trouvee dans aqr\n", l->truc->data.sta.nom);
		}

	//test rechercher
	limite_no = (chercher_station(abr_sta, "St Michel Notre Dame")->coord); 
	limite_se = (chercher_station(abr_sta, "Olympiades")->coord); 

	l = chercher_zone(aqr_sta, limite_no, limite_se);

	ecrire_liste(stdout, l);

	detruire_liste(l);

	detruire_aqr(aqr_sta);

	detruire_abr(abr_sta);

	detruire_liste_et_truc(liste_sta);

	detruire_lignes(liste_ligne);

	return EXIT_SUCCESS;
	}
