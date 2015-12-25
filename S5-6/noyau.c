#include <stdlib.h>
#include "noyau.h"
#include <stdio.h>
#include <string.h>

#define TMP_STR_SIZE 128

noyau_t *creer_noyau(unsigned int dim)
{
    noyau_t *n = (noyau_t *)malloc(sizeof(noyau_t));

    n->dim = dim;
    n->coeffs = (int *)malloc(sizeof(int)*dim*dim);

	return n;
}

void detruire_noyau(noyau_t *pn)
{
    if (pn != NULL) {
        free(pn->coeffs);
        free(pn);
    }
}

noyau_t *charger_noyau(char *nom_fichier)
{
    FILE *f = NULL;
    char buffer[TMP_STR_SIZE];
    noyau_t *n = NULL;
    unsigned int tmp_dim, i;

    if ((f = fopen(nom_fichier, "r")) == NULL) {
        fprintf(stderr, "Impossible de lire le fichier\n");
        exit(1);
    }

    fgets(buffer, TMP_STR_SIZE, f);
    sscanf(buffer, "%u\n", &tmp_dim);

    n = creer_noyau(tmp_dim);

    for (i = 0; i < tmp_dim*tmp_dim; i++) {
        fscanf(f, "%d ", n->coeffs+i);
        //printf("%d ", *(n->coeffs+i));
    }

    fclose(f);

    return n;
}

int get_coeff_noyau(noyau_t *n, direction d)
{
    int ind_central = ( (n->dim + 1) >> 1 ) - 1;
    int coeff_central = ind_central * (n->dim + 1);

    int coeff_res;

    switch (d) {

        case gauche:    coeff_res = *(n->coeffs + coeff_central - 1);
                        break;
        case droite:    coeff_res = *(n->coeffs + coeff_central+ 1);
                        break;
        case haut:      coeff_res = *(n->coeffs + coeff_central - n->dim);
                        break;
        case bas:       coeff_res = *(n->coeffs + coeff_central + n->dim);
                        break;
        case haut_gauche:   coeff_res = *(n->coeffs + coeff_central - n->dim - 1);
                            break;
        case haut_droite:   coeff_res = *(n->coeffs + coeff_central - n->dim + 1);
                            break;
        case bas_gauche:    coeff_res = *(n->coeffs + coeff_central + n->dim - 1);
                            break;
        case bas_droite:    coeff_res = *(n->coeffs + coeff_central + n->dim + 1);
                            break;
        case centre:        coeff_res = *(n->coeffs + coeff_central);
                            break;
    }

    return coeff_res;
}

unsigned char normaliser(noyau_t *n, int num)
{
    int somme = 0;
    int i;

    for (i = 0; i < n->dim * n->dim; i++) {
        somme += *(n->coeffs + i);
    }

    if (somme == 0) {
        return (unsigned char) num;
    } else if (somme < 0) {
        return (unsigned char) ((float) num / (float) (-1)*somme);
    } else return (unsigned char) ((float) num / (float) somme);
}
