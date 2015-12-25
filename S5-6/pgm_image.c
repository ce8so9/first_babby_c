#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "image.h"
#include "pgm_image.h"

#define TMP_STR_SIZE 256

image_t *charger_image_pgm(char *nom_fichier)
{
	FILE *f = NULL;
	image_t *img = NULL;
	unsigned short nb_niveaux_de_gris;
	char buffer[TMP_STR_SIZE];
    char *line;
    pgm_form img_format;

    int i;
    //int j;

    if ((f = fopen(nom_fichier, "r")) == NULL) {
        fprintf(stderr, "Impossible de lire %s\n", nom_fichier);
        return img;
    }

    if ((line = fgets(buffer, TMP_STR_SIZE, f)) == NULL) {
        fprintf(stderr, "Fichier %s vide\n", nom_fichier);
        return img;
    }

    if ((strcmp(line, "P2\n") != 0) && (strcmp(line, "P5\n") != 0)) {
        fprintf(stderr, "Format du fichier %s incorrect\n", nom_fichier);
        return img;
    }

    if (strcmp(line, "P2\n") == 0)
        img_format = ASCII;
    else if (strcmp(line, "P5\n") == 0)
        img_format = BIN;

    img = creer_image();
    line = fgets(buffer, TMP_STR_SIZE, f);
    
    while (buffer[0] == '#') line = fgets(buffer, TMP_STR_SIZE, f);

    sscanf(line, "%lu %lu\n", &(img->w), &(img->h));
    line = fgets(buffer, TMP_STR_SIZE, f);
    sscanf(line, "%hu\n", &nb_niveaux_de_gris);
    img->buff = (unsigned char *)malloc(sizeof(unsigned char)*(img->w * img->h));
    
    if (img_format == ASCII) {
        for (i = 0; i < img->h * img->w; i++) 
                fscanf(f, "%hhu", img->buff+i);
    } else if (img_format == BIN) {
        if (fread(img->buff, img->w, img->h, f) != img->h) {
            fprintf(stderr, "Format impossible à lire\n");
        }
    }

    img->path = strdup(nom_fichier);

    fclose(f);
	return img;
}

int sauver_image_pgm(char *nom_fichier, image_t *img)
{
    FILE *f;

    if (img == NULL) {
        fprintf(stderr, "Impossible de sauvegarder une image vide\n");
        return 0;
    }

    if ((f = fopen(nom_fichier, "w")) == NULL) {
        fprintf(stderr, "Impossible de lire %s\n", nom_fichier);
        return 0;
    }
    
    fprintf(f, "P5\n");
    fprintf(f, "%lu %lu\n", img->w, img->h);
    fprintf(f, "%d\n", 255);  

    if (fwrite(img->buff, img->w, img->h, f) != img->h) {
        fprintf(stderr, "L'enregistrement a echoue\n");
    }
    
    fclose(f);

	return 1;
}
