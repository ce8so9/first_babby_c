#include <stdbool.h>
#include "utilitaires_tableaux.h"

void triBulle(int tab[], int n)
{
    int i;
    int j;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (tab[j] > tab[j+1]) {
                echanger_elem_tab(tab, j, j+1);
            }
        }
    }
}

void triBulleOptimise(int tab[], int n)
{
    int i;
    int j;
    bool swap_flag;

    for (i = 0; i < n-1; i++) {
        swap_flag = false;
        for (j = 0; j < n-i-1; j++) {
            if (tab[j] > tab[j+1]) {
                echanger_elem_tab(tab, j, j+1);
                swap_flag = true;
            }
        }
        if (swap_flag == false) {
            break;
        }
    }
}
