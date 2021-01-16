#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "err.h"

Image* new_image(int width, int height) {
    int size = width * height;
    Image *img = malloc(sizeof(Image));
    img->width = width;
    img->height = height;
    img->data_size = size;
    img->data = malloc(sizeof(Pixel)*size);
    return img;
}

int free_image(Image* img) {
    free(img->data);
    free(img);
    return 0;
}

/**
 * Reads .ppm image from a FILE
*/
Image* read_image(FILE* stream) {
    size_t line_len;
    Image *img = malloc(sizeof(Image));
    img->header = malloc(sizeof(void*)*256);
    int *size = &img->header_size;
    *size = 1;
    
    /* format check */
    getline(&img->header[0], &line_len, stream);
    *size += 1;
    if(!strcmp(img->header[0], "P6")) err(ERR_UNSUPORTED_FORMAT);

    while (1) {
        getline(&img->header[*size-1], &line_len, stream);
        if(img->header[*size-1][0] != '#') break;
        if(*size > 256) err(ERR_UNSUPORTED_FORMAT);
        *size += 1;
    }
    
    getline(&img->header[*size], &line_len, stream);
    *size += 1;

    sscanf(img->header[*size-2], "%d %d", &img->width, &img->height);
    //sscanf(img->header[*size-1], "%d", &img->bitdepth);
    img->data_size = img->width * img->height;
    img->data = malloc(img->data_size * sizeof(Pixel));
    fread(img->data, sizeof(Pixel), img->data_size, stream);

    return img;
}

int write_image(FILE* file, Image *img) {
    return 0;
}

