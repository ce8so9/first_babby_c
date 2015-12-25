#include "dijkstra.h"

void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep)
{
	Un_elem *curr = NULL;

	curr = liste_sta;

	sta_dep->user_val = 0.0;	// 1.

	while (curr != NULL) 		// 2.
		curr->user_val = INFINI;

	

}

Un_elem *cherche_chemin(Un_truc *sta_arr)
{

}