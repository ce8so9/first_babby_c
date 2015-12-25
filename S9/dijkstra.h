#ifndef DIJKS
#define DIJKS

/* includes */
#include "liste.h"
#include "truc.h"

#define INFINI 9999.9

void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep);

Un_elem *cherche_chemin(Un_truc *sta_arr);

#endif
