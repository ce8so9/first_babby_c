#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int compte_mots_chaine(char *chaine)
{
    int etat = 0;
    int compteur = 0;
    int i = 0;

    while (chaine[i] != '\0') {
        switch (etat) {
        case 0: 
            if (isspace(chaine[i]) == 0) {
                etat = 1;
                compteur++;
            } break;
        case 1:
            if (isspace(chaine[i]) != 0) 
                etat = 0;
            break;
        }
        i++;
    }

    return compteur;
}

char **decompose_chaine(char *chaine) 
{
    int i = 0;
    int m = 0;
    int nbre_de_mots = compte_mots_chaine(chaine);
    char **tab = malloc((nbre_de_mots+1)*sizeof(char*));

    while (chaine[i] != '\0') {
        while (isspace(chaine[i])) i++; //Discard whitespaces

        int b = i; //Beginning of word
        //Get a complete word
        while (!(isspace(chaine[i]) || chaine[i] == '\0')) i++; 

        char* word = malloc(i-b+1);
        strncpy(word, chaine+b, i-b+1);
        word[i-b] = '\0';

        tab[m] = word;
        m++;
    }

    tab[m] = NULL;
    return tab;
}

char *compose_chaine(char **ptab_mots)
{
    int i = 0;
    int nbre_char_chaine = 0;

    while (ptab_mots[i] != NULL) {
        nbre_char_chaine += (strlen(ptab_mots[i])+1);
        i++;
    }

    char *chaine = malloc(nbre_char_chaine*sizeof(char));
    i = 0;

    while (ptab_mots[i] != NULL) {
        strcat(chaine, ptab_mots[i]);
        int nbre_char = strlen(chaine);
        chaine[nbre_char] = ' ';
        i++;
    }
    
    chaine[nbre_char_chaine] = '\0';
    return chaine;

}
		
char **detruit_tab_mots(char **ptab_mots)
{
    int i = 0;

    while (ptab_mots[i] != NULL) {
        free(ptab_mots[i]);
        i++;
    }

    free(ptab_mots);
    return NULL;
}

int compte_mots(char **ptab_mots)
{
    int nbre_de_mots;
    int i = 0;

    while (ptab_mots != NULL) {
        nbre_de_mots += 1;
        i++;
    }

    return nbre_de_mots;
}

void affiche_tab_mots(char **ptab_mots)
{
    int i = 0;

    while (ptab_mots[i] != NULL) {
        printf("%s Adresse memoire : %p\n", ptab_mots[i], ptab_mots[i]);
        i++;
    }
}

char **reduit_tab_mots(char **ptab_mots)
{
    int i = 0;
    int j = 1;

    while (ptab_mots[i] != NULL) {
        while (ptab_mots[j] != NULL) {
            if (ptab_mots[i] == ptab_mots[j-i]) j++;
            if (strcmp(ptab_mots[i], ptab_mots[j-i]) == 0) {
                free(ptab_mots[j-i]);
                ptab_mots[j-i] = ptab_mots[i];
            }
            j++;
            
        }
        i++;
        j = i+1;
    }

    return ptab_mots;
}

