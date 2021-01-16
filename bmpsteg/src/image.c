#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "err.h"

int image_tap(Image* imgp) {
    int i, j;
    for (i = 0; i < imgp->data_size; i++) {
        printf("%x %x %x", imgp->data[i].r, imgp->data[i].g, imgp->data[i].b);
        if (i % imgp->width) printf(" ");
        else printf("\n");
    }
}

int image_invert(Image* imgp) {
    int i;
    for (i = 0; i < imgp->data_size; i++) {
        Pixel* pix = &imgp->data[i];
        pix->r = 0xFF - pix->r;
        pix->g = 0xFF - pix->g;
        pix->b = 0xFF - pix->b;
    }
}