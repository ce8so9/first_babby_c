#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float p_ch_dir=0.01;
float d_proie=1;
float d_predateur=1;
float p_manger=0.2;
float p_reproduce=0.01;
float energie=50;

int main(void) 
{
	Animal *lproie = creer_animal(3, 3, energie);
	Animal *lpred = creer_animal(6, 9, energie);
	unsigned int compteur_it, compteur_rec;

	Animal **direct_proie = NULL;
	direct_proie = &lproie;
	Animal **direct_pred = NULL;
	direct_pred = &lpred;

	ajouter_animal(5, 4, direct_proie);
	ajouter_animal(2, 6, direct_proie);
	ajouter_animal(14, 4, direct_proie);
	ajouter_animal(15, 8, direct_proie);

	ajouter_animal(10, 8, direct_pred);
	ajouter_animal(8, 8, direct_pred);
	ajouter_animal(4, 8, direct_pred);

	compteur_rec = compte_animal_rec(lproie);
	compteur_it = compte_animal_it(lpred);

	afficher_ecosys(lpred, lproie);
	printf("\nIl y a %u proies pour %u predateurs.\n", compteur_rec, compteur_it);
    
	return 0;
}
