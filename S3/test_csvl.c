/*
 * =====================================================================================
 *
 *       Filename:  test_csv1.c
 *
 *    Description:  s
 *
 *        Version:  1.0
 *        Created:  09/29/2012 11:40:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "csvl.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *phrase = "banane et poire et pomme et banane";
    printf("%s\n", phrase);

    char **tab = decompose_chaine(phrase);
    affiche_tab_mots(tab);
    
    char *phrase2 = compose_chaine(tab);
    printf("%s\n", phrase2);

    char **tab2 = reduit_tab_mots(tab);
    affiche_tab_mots(tab2);

    detruit_tab_mots(tab);

    free(phrase2);


    return 0;
}


