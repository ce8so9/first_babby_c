#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"

image_t *creer_image()
{
	image_t *p = (image_t *)malloc(sizeof(image_t));

	if (p == NULL)
		printf("Allocation impossible!\n");

	p->w = 0;
	p->h = 0;
	p->path = NULL;
	p->buff = NULL;

	return p;
}

void init_image(image_t *src, image_t *dest)
{
    dest->w = src->w;
    dest->h = src->h;
    dest->path = strdup(src->path);
    dest->buff = (unsigned char *)malloc(sizeof(unsigned char)*(src->w * src->h));
}

void detruire_image(image_t *p)
{
	if (p != NULL) {
		free(p->buff);
		free(p->path);
		free(p);
	}
}

image_t *copier_image(image_t *src)
{
	image_t *copie = creer_image();

    copie->w = src->w;
    copie->h = src->h;

    copie->path = (char *)malloc(sizeof(char)*(strlen(src->path)+1));
    strcpy(copie->path, src->path);
    
    copie->buff = (unsigned char*)malloc(sizeof(char)*(src->w)*(src->h));
    memcpy(copie->buff, src->buff, (src->w)*(src->h));

    return copie;
}

