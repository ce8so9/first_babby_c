#include <stdio.h>
#include <stdlib.h>

#define DIM 8
#define false 0
#define true !false

int labyrinthe[DIM][DIM] = { 	{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 0, 1, 0, 1, 0},
                                {1, 0, 1, 1, 1, 0, 0, 0},
                                {1, 0, 0, 1, 0, 0, 1, 1},
                                {0, 1, 0, 1, 0, 1, 0, 1},
                                {0, 0, 0, 1, 0, 1, 0, 1},
                                {1, 1, 1, 1, 0, 0, 0, 0}
                            };

char nouvellepalette[4] = {' ', '*', '2', '3'}; 

void afficher_lab(int lab[DIM][DIM], char palette[])
{
	int i, j;
	
	printf("+--------+\n");

	for (i = 0; i < DIM; i++) {
		printf("|");
		for (j = 0; j < DIM; j++) {
			printf("%c", palette[lab[i][j]]);
		}
		printf("|\n");
	}

	printf("+--------+\n");
     
}

int chercher_chemin_rec(int lab[DIM][DIM], int lc, int cc)
{
    int resultat_recherche;
    
    afficher_lab(lab, nouvellepalette);

    if (lc > 7 || lc < 0 || cc < 0 || cc > 7) { 
        return false;
    } else if (lc == 7 && cc == 7) {
        return true;
    } else if (lab[lc][cc] == 1) {
        printf("obstacle en (%d, %d)\n", cc, lc);
        return false;
    } else if (lab[lc][cc] == 2) {
        printf("(%d, %d) déja visité\n", cc, lc);
        return false;  
    } else if (lab[lc][cc] == 3) {
        return false;
    }

    lab[lc][cc] = 2;

    /* ordre de priorité: bas, droite, haut puis gauche */

    if (chercher_chemin_rec(lab, lc + 1, cc)) {
        return true;
    } else if (chercher_chemin_rec(lab, lc, cc + 1)) {
        return true;
    } else if (chercher_chemin_rec(lab, lc - 1, cc)) {
        return true;
    } else if (chercher_chemin_rec(lab, lc, cc - 1)) {
        return true;
    }

    lab[lc][cc] = 3;
    return false;
}

int chercher_chemin(int lab[DIM][DIM])
{	
	int abscisse = 0, ordonnee = 0;
    if (chercher_chemin_rec(lab, ordonnee, abscisse)){
        printf("Chemin trouvé!\n");
        return true;
    } else {
        printf("Pas de chemin.\n");
        return false;
    }
}

int main(void)
{
        chercher_chemin(labyrinthe);
		return true;    

}
