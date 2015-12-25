#include "truc.h"

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv)
{
	Un_truc *t = NULL;

	if ( (t = (Un_truc *)malloc(sizeof(Un_truc))) == NULL) {
		fprintf(stderr, "Allocation impossible");
		return NULL;
	} 

	t->coord = coord;
	t->type = type;
	t->data = data;
	t->user_val = uv;

	return t;
}

void detruire_truc(Un_truc *truc)
{
	if (truc->type == STA) {
		free(truc->data.sta.nom);
		free(truc->data.sta.tab_con);
	}

	free(truc);
}
