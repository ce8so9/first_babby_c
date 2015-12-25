#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilitaires_tableaux.h"
#include "tri_bulle.h"

#define TAILLE 100

int main(void)
{
    int tableau[TAILLE];
    
    srand(time(NULL));
    init_tab_alea(tableau, TAILLE);
    
    afficher_tab(tableau, TAILLE);
    triBulleOptimise(tableau, TAILLE);
    afficher_tab(tableau, TAILLE);

    if (tab_trie(tableau, TAILLE) == 0) {
        fprintf(stderr, "Le tableau n'est pas trié.\n");
    } else {
        printf("Le tableau est trié.\n");
    }

}
