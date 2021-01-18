#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "err.h"

/*=-------------------------------------------------------------------------=*/
/* 
int imgx(Image* imgp, int i) {
    if (i >=imgp->data_size) return -1;
    return i % imgp->width;
}

int imgy(Image* imgp, int i) {
    if (i >= imgp->data_size) return -1;
    return i / imgp->width;
}

int imgi(Image* imgp, int x, int y) {
    if (x >= imgp->width || y >= imgp->height) return -1;
    return imgp->width * y + x;
}
*/
/*=-------------------------------------------------------------------------=*/

int image_read_ppm(Image* imgp, FILE* imgin) {
    size_t len;
    char* line = NULL;
    int res;

    /* format check */
    res = getline(&line, &len, imgin);
    if (!strcmp(line, "P6")) err(ERR_UNSUPORTED_FORMAT);

    while (getline(&line, &len, imgin) != -1 && line[0] == '#');

    sscanf(line, "%d %d", &imgp->width, &imgp->height);
    imgp->data_size = imgp->width * imgp->height;

    getline(&line, &len, imgin);
    sscanf(line, "%d", &imgp->bitdepth);
    
    imgp->data = malloc(imgp->data_size * sizeof(Pixel));
    int result = fread(imgp->data, sizeof(Pixel), imgp->data_size, imgin);

    return 0;
}

int image_write_ppm(Image* imgp, FILE* imgout) {
    fprintf(imgout, "P6\n");
    fprintf(imgout, "%d %d\n", imgp->width, imgp->height);
    fprintf(imgout, "%d\n", imgp->bitdepth);
    fwrite(imgp->data, imgp->data_size, sizeof(Pixel), imgout);
    return 0;
}

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
        pix->r = 0xFF ^ pix->r;
        pix->g = 0xFF ^ pix->g;
        pix->b = 0xFF ^ pix->b;
    }
}

int image_scale_nn(Image* imgp, int nw, int nh) {
    int i;
    int nsize = nw * nh;
    double sx = (double)nw / imgp->width;
    double sy = (double)nh / imgp->height;

    Pixel* datp = malloc(nsize * sizeof(Pixel));

    for (i = 0; i < nsize; i++) {
        int nx = i % nw;
        int ny = i / nw;
        int ox = (int)(nx/sx);
        int oy = (int)(ny/sy);
        datp[i] = imgp->data[ox + oy * imgp->height];
    }

    free(imgp->data);
    imgp->data = datp;
    imgp->width = nw;
    imgp->height = nh;
    imgp->data_size = nsize;
}

int image_dither(Image* imgp) {
    int i;
    int w = imgp->width;
    int h = imgp->height;
    Pixel* px = imgp->data;

    for (i = 0; i < imgp->data_size; i++) {
        int oluma = (px[i].g + px[i].g + px[i].b) / 3;
        int nluma = oluma > 127 ? 255 : 0;
        int dluma = oluma - nluma;
        if(i%w)
            px[i+1].g += MIN(dluma * 7.0/16.0, 255);
        if(i/w != h) {
            px[i+w-1].g += MIN(dluma * 3.0/16.0, 255);
            px[i+w  ].g += MIN(dluma * 5.0/16.0, 255);
            px[i+w+1].g += MIN(dluma * 1.0/16.0, 255);
        }

        px[i].r = nluma;
        px[i].g = nluma;
        px[i].b = nluma;
    }
}

int image_kernel_filter(Image* imgp, Kernel kernel) {
    int i;
    int j;
    int kw = kernel.size;
    double ksum = 0;
    Pixel* data = malloc(imgp->data_size * sizeof(Pixel));

    for (i = 0; i < imgp->data_size; i++) {
        double r = 0;
        double g = 0;
        double b = 0;
        ksum = 0;

        for (j = 0; j < kw*kw; j++) {
            int ix = (i % imgp->width) + (j % kw - kernel.size + 1);
            int iy = (i / imgp->width) + (j / kw - kernel.size + 1);
            int ii = imgp->width * iy + ix;

            if (ix < 0 || iy < 0) continue;
            if (ii >= imgp->data_size || ii < 0) continue;

            r += imgp->data[ii].r * kernel.data[j];
            g += imgp->data[ii].g * kernel.data[j];
            b += imgp->data[ii].b * kernel.data[j];
            ksum += kernel.data[j];
        }
        data[i].r = (int)MINMAX(r / ksum, 0, 255);
        data[i].g = (int)MINMAX(g / ksum, 0, 255);
        data[i].b = (int)MINMAX(b / ksum, 0, 255);
    }

    free(imgp->data);
    free(kernel.data);
    imgp->data = data;
}

int image_resize(Image* imgp, int w, int h, int x, int y) {
    int i;
    Pixel* data = malloc(w * h * sizeof(Pixel));

    for ( i = 0; i < w * h; i++) {
        int ix = i % w - x;
        int iy = i / w - y;
        if (ix >= imgp->width || ix < 0) continue;
        if (iy >= imgp->height || iy < 0) continue;
        int ii = imgp->width * iy + ix;
        data[i] = imgp->data[ii];
    }

    free(imgp->data);
    imgp->data = data;
    imgp->width = w;
    imgp->height = h;
    imgp->data_size = w * h;
}

int image_compose(Image* img1p, Image* img2p, int x, int y) {
    int i;

    for ( i = 0; i < img2p->data_size; i++) {
        int ix = i % img2p->width + x;
        int iy = i / img2p->height + y;
        if (ix >= img1p->width || ix < 0) continue;
        if (iy >= img1p->height || iy < 0) continue;
        int ii = img1p->width * iy + ix;
        img1p->data[ii] = img2p->data[i];
    }
}

int image_contrast(Image* imgp, double x) {
    int i;

    for ( i = 0; i < imgp->data_size; i++) {
        imgp->data[i].r = CLAMP(((imgp->data[i].r - 256/2) * x ) + 256/2);
        imgp->data[i].g = CLAMP(((imgp->data[i].g - 256/2) * x ) + 256/2);
        imgp->data[i].b = CLAMP(((imgp->data[i].b - 256/2) * x ) + 256/2);
    }
}

/* TODO: implement */

int image_brightness(Image* imgp, int db) {
    int i;
    for (i = 0; i < imgp->data_size; i++) {
        imgp->data->r += db;
        imgp->data->g += db;
        imgp->data->b += db;
    }
}


int image_hue(Image* imgp, int dh) {

}

int image_perspective(Image* imgp, Point nw, Point ne, Point sw, Point se) {
    /**
     *  nw--ne
     *  |    |
     *  sw--se
    */
    int i;
    Pixel temp;
    Pixel* datp = malloc(imgp->data_size * sizeof(Pixel));
    int w = imgp->width;
    int h = imgp->height;

    for (i = 0; i < imgp->data_size; i++) {
        Point curr = {i % w, i / w};
    }
}

/*=-------------------------------------------------------------------------=*/

Kernel kernel_normalized(int size) {
    int i;
    Kernel k;
    k.size = size;
    k.data = malloc(k.size * k.size * sizeof(double));
    for (i = 0; i < size * size; i++) k.data[i] = 1;
    return k;
}

Kernel kernel_sobel(int size) {
    Kernel k;
    k.size = 3;
    k.data = malloc(k.size* k.size * sizeof(double));
    k.data[0] = 0; k.data[1] = 1;  k.data[2] = 0;
    k.data[3] = -1;  k.data[4] = 5;  k.data[5] = -1;
    k.data[6] = 0;  k.data[7] = -1;  k.data[8] = 0;
    return k;
}