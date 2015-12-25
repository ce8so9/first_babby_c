#ifndef UTILITAIRES_TABLEAUX
#define UTILITAIRES_TABLEAUX

/*****************************************************************************/
/* Ensemble de fonctions facilitant la manipulation de tableaux d entiers.   */
/*****************************************************************************/

/*****************************************************************************/
/* Affiche les n premiers elements d'un tableau tab, 10 elements par ligne.  */
/*****************************************************************************/
extern void afficher_tab(int tab[], int n);

/*****************************************************************************/
/* Initialise les n premiers elements d'un tableau tab avec des valeurs      */
/* generees aleatoirement entre 0 et val_max [0,val_max[. val_max est une    */
/* variable globale de votre programme.                                      */
/*****************************************************************************/
extern void init_tab_alea(int tab[], int n);

/*****************************************************************************/
/* Copie les n premiers elements du tableau tabSrc dans le tableau tabDst.   */
/*****************************************************************************/
extern void copier_tab(int tabSrc[], int tabDest[], int n);

/*****************************************************************************/
/* Echange les elements d indice i et j du tableau tab.                      */
/*****************************************************************************/
extern void echanger_elem_tab(int tab[], int i, int j);

/*****************************************************************************/
/* Returne 1 si les n premiers elements du tableau tab sont tries par ordre */
/* croissant, retourne 0 sinon.                                              */
/*****************************************************************************/
int tab_trie(int tab[], int n);

#endif
