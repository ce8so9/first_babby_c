#include "repertoire.h"

int main()
{
    char *fichier = "repertoire.txt";
    Contact *c = nouveau_contact();

    set_nom_prenom(c, "Mance", "Roy");
    c->date_naissance.jour = 43;
    c->date_naissance.mois = 22;
    c->date_naissance.annee = 12;
    strcpy(c->telephone, "0123456789");
    c->adresse.code_postal = 66666;
    strcpy(c->adresse.ville, "Hell");
    afficher_contact(c);
    liberer_contact(c);

    Contact *rep = cree_repertoire(50000);
    int i = 0;
    char str[20];
    
    for (; i < 50000; i++) {
        sprintf(str, "Sinnern%d\n", i);
        set_nom_prenom(rep+i, str, str);
        set_date(rep+i, i % 127, i % 127, i);
        set_telephone(rep+i, "0123456789");
        set_adresse(rep+i, "1313 NyukNyukNyuk", 66666, "Hell");
    }

    ecrire(rep, 50000, fichier);

    Contact *rep2 = NULL;
    unsigned int nu = 0;
    int j = 0;
    lire(fichier, rep2, &nu);

    for(; j < nu; j++) {
        afficher_contact(rep2+j);
    }

    free(rep);
    free(rep2);

    return 0;
}
