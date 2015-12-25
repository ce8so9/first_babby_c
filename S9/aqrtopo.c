#include "aqrtopo.h"
#include "liste.h"

Un_noeud *creer_noeud(Une_coord limit_no, Une_coord limit_se, Un_truc *truc)
{
    Un_noeud *n = NULL;

    n = (Un_noeud *)malloc(sizeof(Un_noeud));

    n->truc = truc;
    n->limite_no = limit_no;
    n->limite_se = limit_se;
    n->no = NULL;
    n->so = NULL;
    n->ne = NULL;
    n->se = NULL;

    return n;
}

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    Un_noeud *new_n, *new_n2 = NULL;
    Un_noeud *pere = NULL;
    Un_noeud *pt_n = NULL;
    float lon = 0.0;
    float lat = 0.0;

    pt_n = aqr;

    while (pt_n != NULL && pt_n->truc == NULL) {

        pere = pt_n;

        lon = (pt_n->limite_no.lon + pt_n->limite_se.lon) / 2;
        lat = (pt_n->limite_no.lat + pt_n->limite_se.lat) / 2;

        if (truc->coord.lon < lon) {
            if (truc->coord.lat < lat)
                pt_n = pt_n->so;
            else pt_n = pt_n->se;
        } else if (truc->coord.lat < lat) {
            pt_n = pt_n->no;
        } else
            pt_n = pt_n->ne;
    }

    if (pt_n == NULL) {
        if (pere == NULL)
            pt_n = creer_noeud(limite_no, limite_se, truc);
        else {
            if (truc->coord.lon < lon) {
                if (truc->coord.lat < lat)
                    pt_n->so = creer_noeud(limite_no, limite_se, truc);
                else pt_n->se = creer_noeud(limite_no, limite_se, truc);
            } else if (truc->coord.lat < lat) {
                pt_n->no = creer_noeud(limite_no, limite_se, truc);
            } else
                pt_n->ne = creer_noeud(limite_no, limite_se, truc);
        }
    } else {
        new_n = creer_noeud(limite_no, limite_se, truc);    

        if (truc->coord.lon < lon) {
            if (truc->coord.lat < lat)
                pt_n->so = new_n;
            else pt_n->se = new_n;
        } else if (truc->coord.lat < lat) {
            pt_n->no = new_n;
        } else
            pt_n->ne = new_n;

        new_n2 = creer_noeud(limite_no, limite_se, pt_n->truc); 

        if (pt_n->truc->coord.lon < lon) {
            if (pt_n->truc->coord.lat < lat)
                pt_n->so = new_n2;
            else pt_n->se = new_n2;
        } else if (pt_n->truc->coord.lat < lat) {
            pt_n->no = new_n2;
        } else
            pt_n->ne = new_n2;

        pt_n->truc = NULL;

    }

    return aqr;
}

Un_noeud *construire_aqr(Un_elem *liste)
{
    Un_elem *curr = NULL;
    Un_noeud *a = NULL;
    Une_coord no, se;

    curr = liste;
    limites_zone(curr, &no, &se);
    curr = liste;

    while (curr != NULL) {
        if (a == NULL)
            a = creer_noeud(no, se, liste->truc);
        else
            a = inserer_aqr(a, no, se, liste->truc);

        curr = curr->suiv;
    }

    return a;
}

void detruire_aqr(Un_noeud *aqr)
{
    if (aqr != NULL) {
        detruire_aqr(aqr->no);
        detruire_aqr(aqr->so);
        detruire_aqr(aqr->ne);
        detruire_aqr(aqr->se);
        free(aqr);
    }
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord)
{
    Un_truc *pt_t = NULL;
    Un_noeud *pt_n = NULL;
    float longitude = 0.0;
    float latitude = 0.0;

    pt_n = aqr;

    while (pt_n != NULL && pt_n->truc == NULL) {
        longitude = (pt_n->limite_no.lon + pt_n->limite_se.lon) / 2;
        latitude = (pt_n->limite_no.lat + pt_n->limite_se.lat) / 2;

        if (coord.lon < longitude) {
            if (coord.lat < latitude)
                pt_n = pt_n->so;
            else pt_n = pt_n->se;
        } else if (coord.lat < latitude) {
            pt_n = pt_n->no;
        } else
            pt_n = pt_n->ne;
    }

    if (pt_n != NULL && pt_n->truc != NULL) {
        if (pt_n->truc->coord.lat == coord.lat && pt_n->truc->coord.lon == coord.lon)
            pt_t = pt_n->truc;
    }

    return pt_t;
}

Un_elem *chercher_zone(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se)
{
    Un_noeud *curr_node = NULL;
    Un_elem *new_list, *new_elem, *curr_elem = NULL;
    float longitude, latitude = 0.0;

    curr_node = aqr;

    while (curr_node != NULL && curr_node->truc == NULL) {

        longitude = (limite_no.lon + limite_se.lon) / 2;
        latitude = (limite_no.lat + limite_se.lat) / 2;

        if (curr_node->truc->coord.lon > limite_no.lon && curr_node->truc->coord.lat < limite_no.lat && 
                curr_node->truc->coord.lon < limite_se.lon && curr_node->truc->coord.lat > limite_no.lat) {
            if (new_list == NULL) {
                new_list = (Un_elem *) malloc(sizeof(Un_elem));
                new_list->truc = curr_node->truc;
                new_list->suiv = NULL;
                curr_elem = new_list;
            } else {
                new_elem = (Un_elem *) malloc(sizeof(Un_elem));
                new_elem->truc = curr_node->truc;
                new_elem->suiv = NULL;
                curr_elem->suiv = new_elem;
                curr_elem = curr_elem->suiv;

                if (curr_node->truc->coord.lon < longitude) {
                    if (curr_node->truc->coord.lat < latitude)
                        curr_node = curr_node->so;
                    else curr_node = curr_node->se;
                } else if (curr_node->truc->coord.lat < latitude) {
                    curr_node = curr_node->no;
                } else
                    curr_node = curr_node->ne;
            }
        } else {
            if (curr_node->truc->coord.lon < longitude) {
                if (curr_node->truc->coord.lat < latitude)
                    curr_node = curr_node->so;
                else curr_node = curr_node->se;
            } else if (curr_node->truc->coord.lat < latitude) {
                curr_node = curr_node->no;
            } else
                curr_node = curr_node->ne;
            }
    }

    return new_list;


}

/*int hauteur_aqr(Un_noeud *aqr)
{
    if (aqr->no == NULL || aqr->ne == NULL || aqr->so == NULL || aqr->se == NULL) 
        return 0;
    else return 1 + max(hauteur_aqr(aqr->no), hauteur_aqr(aqr->ne), hauteur_aqr(aqr->so), hauteur_aqr(aqr->se));
}*/

