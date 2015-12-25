#ifndef NOYAU_
#define NOYAU_

typedef struct {
	unsigned int dim;
	int *coeffs;
} noyau_t;

typedef enum {gauche, droite, haut, bas, haut_gauche, haut_droite, bas_gauche, bas_droite, centre} direction;

noyau_t *creer_noyau(unsigned int dim);
void detruire_noyau(noyau_t *pn);
noyau_t *charger_noyau(char *nom_fichier);
int get_coeff_noyau(noyau_t *n, direction d);
unsigned char normaliser(noyau_t *n, int num);

#endif
