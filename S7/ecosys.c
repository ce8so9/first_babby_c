#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ecosys.h"

Animal *creer_animal(int x, int y, float energie) 
{
    Animal *a = (Animal *)malloc(sizeof(Animal));
    
    a->x = x;
    a->y = y;
    a->energie = energie;

    srand(time(NULL));
    a->dir[0] = (rand() % 2) - 1;
    a->dir[1] = (rand() % 2) - 1;

    a->precedent = NULL;
    a->suivant = NULL;

    return a;
} 

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal)
{
    Animal *a = NULL;

    if (liste != NULL) {
        a = animal;
        liste->precedent = a;
        a->suivant = liste;
        a->precedent = NULL;
    }

    return a;
}

void ajouter_animal(int x, int y, Animal **liste_animal) 
{
    Animal *a = NULL;
    Animal *l = NULL;

    if ( (x < 0 || y < 0) || (x > SIZE_X || y > SIZE_Y) ) {
        fprintf(stderr, "Coordonnees erronees!");
        return;
    } else {
        a = creer_animal(x, y, energie);
        l = *liste_animal;
        l = ajouter_en_tete_animal(l, a);
        *liste_animal = l;
    }
}


void enlever_animal(Animal **liste, Animal *animal) 
{
    Animal *l = NULL;

    if (animal == NULL) return;

    l = *liste;

    while (l != animal)
        l = l->suivant;

    if (l == animal) {
        
        if (animal->precedent == NULL && animal->suivant == NULL) {
            free(animal);
            return;  
        } else if (animal->suivant == NULL) {
            animal->precedent->suivant = NULL;
        } else if (animal->precedent == NULL) {
            animal->suivant->precedent = NULL;
            *liste = animal->suivant;
        } else {
            animal->precedent->suivant = animal->suivant;
            animal->suivant->precedent = animal->precedent;
        }
    }

    free(animal);
}

unsigned int compte_animal_rec(Animal *la) {
  
    if (la == NULL)
        return 0;
    else
        return 1 + compte_animal_rec(la->suivant);
}

unsigned int compte_animal_it(Animal *la) 
{
    unsigned int cpt = 0;

    while (la != NULL) {
      la = la->suivant;
      cpt++;
    }
    
    return cpt;
}

void bouger_animaux(Animal *la) 
{
    Animal *l = NULL;

    if (la == NULL) return;

    l = la;

    while (l != NULL) {

        if (( (float)(rand() % 100) / 100.0 ) < p_ch_dir ) {
            l->dir[0] = (rand() % 2) - 1;
            l->dir[1] = (rand() % 2) - 1;
        }

        l->x += l->dir[0];
        l->y += l->dir[1];

        if (l->x < 0)
            l->x = SIZE_X - 1;
        else if (l->x > SIZE_X - 1)
            l->x = 0;

        if (l->y < 0)
            l->y = SIZE_Y - 1;
        else if (l->y > SIZE_Y - 1)
            l->y = 0;

        l = l->suivant;
    }
}

void reproduce(Animal **liste_animal) 
{
        Animal *l = NULL;

        if (*liste_animal == NULL) return;

        l = *liste_animal;

        while (l != NULL) {
            if (( (float)(rand() % 100) / 100.0 ) < p_reproduce )
                ajouter_animal(l->x, l->y, liste_animal);
            l = l->suivant;
        }

}

void rafraichir_proies(Animal **liste_proie) 
{
    Animal *l = *liste_proie;

    bouger_animaux(*liste_proie);
    
    while (l->suivant != NULL) {
        l->energie -= d_proie;

        if (l->energie < 0)
            enlever_animal(liste_proie, l);

        l = l->suivant;
    }

    reproduce(liste_proie);

}

Animal *animal_en_XY(Animal *l, int x, int y) 
{
    Animal *p_l = NULL;
    if (l == NULL) return p_l;

    p_l = l;

    while (p_l != NULL) {
        if (p_l->x == x && p_l->y == y) break;
        p_l = p_l->suivant;
    }

    return p_l;
} 

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) 
{
    Animal *lpred = NULL;
    Animal *a = NULL;

    bouger_animaux(*liste_predateur);

    lpred = *liste_predateur;

    while (lpred->suivant != NULL) {
        lpred->energie -= d_predateur;

        if (lpred->energie < 0)
            enlever_animal(liste_predateur, lpred);

        if ( (a = animal_en_XY(*liste_proie, lpred->x, lpred->y)) != NULL) {
            lpred->energie += a->energie;
            enlever_animal(liste_proie, a);
        }

        lpred = lpred->suivant;
    }

    reproduce(liste_predateur);
}

void afficher_ecosys(Animal *liste_proie,Animal *liste_predateur) 
{
    Animal *proie_curr = NULL;
    Animal *pred_curr = NULL;
    char monde[SIZE_Y][SIZE_X];
    int i, j;

    proie_curr = liste_proie;
    pred_curr = liste_predateur;

    for (i = 0; i < SIZE_X; i++) {
        for (j = 0; j < SIZE_Y; j++) 
            monde[j][i] = ' ';
    }

    while (proie_curr != NULL) {
        if (monde[proie_curr->y][proie_curr->x] == '*' || monde[proie_curr->y][proie_curr->x] == 'O' || monde[proie_curr->y][proie_curr->x] == '@')
            monde[proie_curr->y][proie_curr->x] = '@';
        else
            monde[proie_curr->y][proie_curr->x] = '*';
        proie_curr = proie_curr->suivant; 
    }
    
    while (pred_curr != NULL) {
        if (monde[pred_curr->y][pred_curr->x] == 'O' || monde[pred_curr->y][pred_curr->x] == '*' || monde[pred_curr->y][pred_curr->x] == '@') 
            monde[pred_curr->y][pred_curr->x] = '@';
        else
            monde[pred_curr->y][pred_curr->x] = 'O';

        pred_curr = pred_curr->suivant;
    }

    for (i = 0; i < SIZE_X + 2; i++) 
        printf("-");

    printf("\n");

    for (i = 0; i < SIZE_X; i++) {
        printf("|");
        for (j = 0; j < SIZE_Y; j++) 
            putchar(monde[j][i]);
        printf("|\n");
    }

    for (i = 0; i < SIZE_X + 2; i++) 
        printf("-");

    printf("\n");
}
