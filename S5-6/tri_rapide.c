#include "utilitaires_tableaux.h"
#include <stdlib.h>
#include <stdio.h>

static int *nouveau_tableau(int n) {
  int *nt = malloc(sizeof(int)*n);
  if (nt == NULL) {
    printf("Erreur lors de la creation d'un tableau (taille=%d)\n",n);
    exit(1);
  }
  return nt;
}

static void detruire_tableau(int *n) {
  free(n);
}

void triRapide(int tab[], int n) {

    int i;
    int j;
    int k = 0;
    int l;
    int tailletabInf = 0;
    int tailletabSup = 0;
    int pivot = tab[0];
    
    if (n == 0 || n == 1) {
      return;
    }
    
    int *tabInf = nouveau_tableau(n);
    int *tabSup = nouveau_tableau(n);

    for (i = 1; i < n; i++) {
        if (tab[i] < pivot) {
            tabInf[tailletabInf] = tab[i];
            tailletabInf++;
        } else {
            tabSup[tailletabSup] = tab[i];
            tailletabSup++;
        }
    }
    
    triRapide(tabInf, tailletabInf);
    triRapide(tabSup, tailletabSup);

    for (l = 0; l < tailletabInf; l++) {
        tab[l] = tabInf[l];
    }


    tab[tailletabInf] = pivot;

    for (j = tailletabInf+1; j < n; j++) {
        tab[j] = tabSup[k];
        k++;
    }

    detruire_tableau(tabInf);
    detruire_tableau(tabSup);
}


static int partitionner(int tab[], int n)
{
    int i;
    int pivot = tab[0];
    int positionDuPivot = 0;

    for (i = 1; i < n; i++) {
        if (tab[i] <= pivot) {
            positionDuPivot++;
            echanger_elem_tab(tab, positionDuPivot, i);
        }
    }
    echanger_elem_tab(tab, 0, positionDuPivot);

    return positionDuPivot;
}

void triRapideOptimise(int tab[], int n)
{
    if (n == 0 || n == 1) {
        return;
    }
    int indicePivot = partitionner(tab, n);

    triRapideOptimise(tab, indicePivot);
    triRapideOptimise(tab+indicePivot+1, n-indicePivot-1); 

}
