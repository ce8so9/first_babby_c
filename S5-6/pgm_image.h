#ifndef PGM_IMAGE
#define PGM_IMAGE

typedef enum {BIN, ASCII} pgm_form;

image_t *charger_image_pgm(char *nom_fichier);
int sauver_image_pgm(char *nom_fichier, image_t *img);

#endif
