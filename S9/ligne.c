#include "ligne.h"

#include <errno.h>
#define BUFFER_SIZE 1024

Une_ligne *creer_ligne(char *code, char *color, float vitesse, float intervalle)
{
	Une_ligne *l = NULL;

	l = (Une_ligne *)malloc(sizeof(Une_ligne));
	l->code = code;
	l->color = color;
	l->vitesse = vitesse;
	l->intervalle = intervalle;
	l->suiv = NULL;

	return l;
}

Une_ligne *lire_lignes(char *nom_fichier)
{
	FILE *f;
	char buff[BUFFER_SIZE];
	Une_ligne *l = NULL, *end = NULL;

	if ( (f = fopen(nom_fichier, "r")) == NULL) {
        fprintf(stderr, "lire_lignes(): Cannot open file: %s", strerror(errno));
        return NULL;
	}

    while (fgets(buff, BUFFER_SIZE, f) != NULL) {
        if (buff[0] == '#')  continue; //Skip to next line on comment
        if (buff[0] == '\n') continue; //Skip to next line on empty line

        char *code = strdup(strtok(buff, ";"));
        float v   = atof(strtok(NULL, ";"));
        float intervalle  = atof(strtok(NULL, ";"));
        char *color  = strdup(strtok(NULL, ";"));

        if (strtok(NULL, ";") != NULL) {
          fprintf(stderr, "lire_lignes: Erreur concernant le format");
          continue;
        }

        Une_ligne *ll = creer_ligne(code, color, v, intervalle);
        
        if(l == NULL)
            l = end = ll;
        else {
            end->suiv = ll;
            end = ll;
        }
	}

	fclose(f);

	return l;
}

void afficher_lignes(Une_ligne *lligne)
{
	while (lligne != NULL) {
		fprintf(stdout, "%s %.1f %.1f %s\n", lligne->code, lligne->vitesse, lligne->intervalle, lligne->color);
		lligne = lligne->suiv;
	}
}

void detruire_lignes(Une_ligne *lligne)
{
	if (lligne == NULL) return;

	Une_ligne *curr = lligne;

	while (lligne != NULL) {
		lligne = lligne->suiv;
        free(curr->code);
        free(curr->color);
		free(curr);
		curr = lligne;
	}

}

Une_ligne *chercher_ligne(Une_ligne *lligne, char *code)
{
	Une_ligne *curr = NULL;
	int flag = 0;

	curr = lligne;

	while (curr != NULL) {

		flag = strcmp(code, curr->code);

		if (flag == 0)
			return curr;

		curr = curr->suiv;
	}

	return NULL;

}
