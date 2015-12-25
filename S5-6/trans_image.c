#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "trans_image.h"

image_t *negatif(image_t *src)
{
    unsigned long i = 0;

    image_t *dst = creer_image();
    init_image(src, dst);

    for (; i < (src->w * src->h); i++)
        dst->buff[i] = ~src->buff[i];   // equivalent to (255-x)%256
    
	return dst;
}

image_t *rotation(image_t *src, int angle)
{
    unsigned long i = 0;
    unsigned long cs, ls, cd, ld;

    image_t *dst = creer_image();

    if ((angle % 90) != 0) {
        fprintf(stderr, "Angle incorrect\n");
        return NULL;
    }

    angle = (angle / 90) % 4;

    init_image(src, dst);

    switch (angle) {
        case 1: dst->w = src->h;
                dst->h = src->w;

                for (i = 0; i < (src->w * src->h); i++) {
                    cs = i % src->w;
                    ls = i / src->w;

                    cd = ls;
                    ld = src->w - cs - 1;
                    
                    dst->buff[(ld * dst->w) + cd] = src->buff[i];
                }

                break;
         
        case 2: dst->w = src->w;
                dst->h = src->h;

                for (i = 0; i < (src->w * src->h); i++) {
                    cs = i % src->w;
                    ls = i / src->w;

                    cd = src->w - cs - 1;
                    ld = src->h - ls - 1;
                    
                    dst->buff[(ld * dst->w) + cd] = src->buff[i];
                }

                break;

        
        case 3: dst->w = src->h;
                dst->h = src->w;

                for (ls = 0; ls < src->h; ls++) {
                    for (cs = 0; cs < src->w; cs++) {
                        cd = src->h - ls - 1;
                        ld = cs;
                        dst->buff[(ld * dst->w) + cd] = src->buff[(ls * src->w) + cs];
                    }
                }

                break;
    }
	return dst;
}

image_t *modifier_lumin(image_t *src, int pourcent)
{
    unsigned long i = 0;
    unsigned long tmp;
    float coeff = (float) pourcent / 100.0;

    image_t *dst = creer_image();
    init_image(src, dst);

    for (i = 0; i < (src->w * src->h); i++) {
        tmp = coeff * src->buff[i];
        if (tmp > 255) tmp = 255;
        dst->buff[i] = tmp;
    }

	return dst;
}

image_t *bruiter_image(image_t *src, int pourcent)
{
    unsigned long i;

    image_t *dst = creer_image();
    init_image(src, dst);

    srand(time(NULL));

    for (i = 0; i < src->w * src->h; i++) {
        if (rand() % 100 < pourcent) {
            dst->buff[i] = rand() % 256;
        } else {
            dst->buff[i] = src->buff[i];
        }
    }

	return dst;
}

image_t *filtrer_median(image_t *src)
{      
    unsigned long i;

    image_t *dst = creer_image();
    init_image(src, dst);    

    for (i = 0; i < (src->w * src->h); i++) {

        if (i / src->w == 0 && i % src->w == 0) {   // top_left
            dst->buff[i] = get_median(i, src, haut_gauche);
        } else if (i / src->w == 0 && i % src->w == (src->w -1)) {  //top_right
            dst->buff[i] = get_median(i, src, haut_droite);
        } else if (i / src->w == (src->h - 1) && i % src->w == 0) { //bottom_left
            dst->buff[i] = get_median(i, src, bas_gauche);
        } else if (i / src->w == (src->h - 1) && i % src->w == (src->w -1)) {   //bottom_right
            dst->buff[i] = get_median(i, src, bas_droite);
        } else if (i % src->w > 0 && i % src->w < (src->w - 1) && i / src->w == 0) { //border_up
            dst->buff[i] = get_median(i, src, haut);
        } else if (i % src->w > 0 && i % src->w < (src->w - 1) && i / src->w == (src->h - 1)) {    //border_down
            dst->buff[i] = get_median(i, src, bas);
        } else if (i / src->w > 0 && i / src->w < (src->h - 1) && i % src->w == 0) {   //border_left
            dst->buff[i] = get_median(i, src, gauche);
        } else if (i / src->w > 0 && i / src->w < (src->h - 1) && i % src->w == (src->w - 1)) {    //border_right
            dst->buff[i] = get_median(i, src, droite);
        } else { 
            dst->buff[i] = get_median(i, src, centre);
        }
    }
	return dst;
}

image_t *convoluer(image_t *src, noyau_t *pn)
{
    unsigned long i;
    int res;

    image_t *dst = creer_image();
    init_image(src, dst);

    for (i = 0; i < (src->w * src->h); i++) {

        if (i / src->w == 0 && i % src->w == 0) {   // top_left

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_gauche) + get_coeff_noyau(pn, haut)
                                    + get_coeff_noyau(pn, haut_droite) + get_coeff_noyau(pn, gauche) + get_coeff_noyau(pn, bas_gauche))
                                    + get_coeff_noyau(pn, droite)*src->buff[i+1] + get_coeff_noyau(pn, bas)*src->buff[i + src->w] 
                                    + get_coeff_noyau(pn, bas_droite)*src->buff[i + src->w + 1] ;

                    dst->buff[i] = normaliser(pn, res);
                
        } else if (i / src->w == 0 && i % src->w == (src->w -1)) {  //top_right

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_gauche) + get_coeff_noyau(pn, haut)
                                    + get_coeff_noyau(pn, haut_droite) + get_coeff_noyau(pn, droite) + get_coeff_noyau(pn, bas_droite))
                                    + get_coeff_noyau(pn, gauche)*src->buff[i-1] + get_coeff_noyau(pn, bas)*src->buff[i + src->w] 
                                    + get_coeff_noyau(pn, bas_gauche)*src->buff[i + src->w - 1] ;

                    dst->buff[i] = normaliser(pn, res);

        } else if (i / src->w == (src->h - 1) && i % src->w == 0) { //bottom_left

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_gauche) + get_coeff_noyau(pn, bas)
                                    + get_coeff_noyau(pn, bas_gauche) + get_coeff_noyau(pn, gauche) + get_coeff_noyau(pn, bas_droite))
                                    + get_coeff_noyau(pn, droite)*src->buff[i+1] + get_coeff_noyau(pn, haut)*src->buff[i - src->w] 
                                    + get_coeff_noyau(pn, haut_droite)*src->buff[i - src->w + 1] ;

                    dst->buff[i] = normaliser(pn, res);
                    
        } else if (i / src->w == (src->h - 1) && i % src->w == (src->w -1)) {   //bottom_right

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_droite) + get_coeff_noyau(pn, bas)
                                    + get_coeff_noyau(pn, bas_gauche) + get_coeff_noyau(pn, droite) + get_coeff_noyau(pn, bas_droite))
                                    + get_coeff_noyau(pn, gauche)*src->buff[i-1] + get_coeff_noyau(pn, haut)*src->buff[i - src->w] 
                                    + get_coeff_noyau(pn, haut_gauche)*src->buff[i - src->w - 1] ;

                    dst->buff[i] = normaliser(pn, res);

        } else if (i % src->w > 0 && i % src->w < (src->w - 1) && i / src->w == 0) { //border_up

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_gauche) + get_coeff_noyau(pn, haut_droite) 
                                    + get_coeff_noyau(pn, haut)) + get_coeff_noyau(pn, gauche)*src->buff[i-1]
                                    + get_coeff_noyau(pn, bas_gauche)*src->buff[i + src->w - 1] + get_coeff_noyau(pn, droite)*src->buff[i+1]
                                    + get_coeff_noyau(pn, bas_droite)*src->buff[i + src->w + 1] + get_coeff_noyau(pn, bas)*src->buff[i + src->w];

                    dst->buff[i] = normaliser(pn, res);

        } else if (i % src->w > 0 && i % src->w < (src->w - 1) && i / src->w == (src->h - 1)) {    //border_down

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, bas_gauche) + get_coeff_noyau(pn, bas_droite) 
                                    + get_coeff_noyau(pn, bas)) + get_coeff_noyau(pn, gauche)*src->buff[i-1]
                                    + get_coeff_noyau(pn, haut_gauche)*src->buff[i - src->w - 1] + get_coeff_noyau(pn, droite)*src->buff[i+1]
                                    + get_coeff_noyau(pn, haut_droite)*src->buff[i - src->w + 1] + get_coeff_noyau(pn, haut)*src->buff[i - src->w];

                    dst->buff[i] = normaliser(pn, res);

        } else if (i / src->w > 0 && i / src->w < (src->h - 1) && i % src->w == 0) {   //border_left

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_gauche) + get_coeff_noyau(pn, bas_gauche) 
                                    + get_coeff_noyau(pn, gauche)) + get_coeff_noyau(pn, haut)*src->buff[i - src->w] 
                                    + get_coeff_noyau(pn, haut_droite)*src->buff[i - src->w + 1] + get_coeff_noyau(pn, droite)*src->buff[i+1]
                                    + get_coeff_noyau(pn, bas_droite)*src->buff[i + src->w + 1] + get_coeff_noyau(pn, bas)*src->buff[i + src->w];

                    dst->buff[i] = normaliser(pn, res);

        } else if (i / src->w > 0 && i / src->w < (src->h - 1) && i % src->w == (src->w - 1)) {    //border_right

                    res = src->buff[i] * (get_coeff_noyau(pn, centre) + get_coeff_noyau(pn, haut_droite) + get_coeff_noyau(pn, bas_droite) 
                                    + get_coeff_noyau(pn, droite)) + get_coeff_noyau(pn, haut)*src->buff[i + src->w]
                                    + get_coeff_noyau(pn, haut_gauche)*src->buff[i - src->w - 1] + get_coeff_noyau(pn, gauche)*src->buff[i-1]
                                    + get_coeff_noyau(pn, bas_gauche)*src->buff[i + src->w - 1] + get_coeff_noyau(pn, bas)*src->buff[i + src->w];

                    dst->buff[i] = normaliser(pn, res);

        } else {   

                    res = get_coeff_noyau(pn, centre)*src->buff[i] + get_coeff_noyau(pn, haut_gauche)*src->buff[i - src->w - 1]
                                        + get_coeff_noyau(pn, haut)*src->buff[i - src->w] + get_coeff_noyau(pn, haut_droite)*src->buff[i - src->w + 1]
                                        + get_coeff_noyau(pn, gauche)*src->buff[i-1] + get_coeff_noyau(pn, droite)*src->buff[i+1]
                                        + get_coeff_noyau(pn, bas_gauche)*src->buff[i + src->w - 1] + get_coeff_noyau(pn, bas)*src->buff[i + src->w]
                                        + get_coeff_noyau(pn, bas_droite)*src->buff[i + src->w + 1];

                    dst->buff[i] = normaliser(pn, res);
        }
    }

	return dst;
}


unsigned char get_median(unsigned long n, image_t *s, direction d)
{
    int voisins[25];
    char a, b, l, j;
    int k = 0;
    unsigned char res;

    switch (d) {
        case haut_gauche:   a = 0; b = 0; break; 
        case haut:          a = 0; b = -2; break;
        case haut_droite:   a = 0; b = -4; break;

        case gauche:        a = -2; b = 0; break;
        case centre:        a = -2; b = -2; break;
        case droite:        a = -2; b = -4; break;

        case bas_gauche:    a = -4; b = 0; break;
        case bas:           a = 5; b = 5; break;
        case bas_droite:    a = -4; b = -4; break;
    }

    for (l = a; l < a+5; l++) {
        for (j = b; j < b + 5; j++) {
            voisins[k] = s->buff[n + l * s->w + j];
            k++;
        }
    }

    triRapideOptimise(voisins, k+1);
    res = (unsigned char) voisins[12];

    return res;

}
