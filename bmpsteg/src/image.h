#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <stdio.h>

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    /* raw data from file */
    char **header;
    Pixel *data;
    /* computed/read properties */
    int header_size;
    int data_size;
    int width;
    int height;
} Image;

Image* new_image(int width, int height);
int free_image(Image* img);
Image* read_image(FILE* stream);
int write_image(FILE* stream, Image *img);

#endif /* _IMAGE_H_ */