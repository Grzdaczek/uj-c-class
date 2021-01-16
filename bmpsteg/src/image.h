#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <stdio.h>

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    Pixel *data;
    int data_size;
    int width;
    int height;
    int bitdepth;
} Image;

int image_tap(Image* imgp);
int image_invert(Image* imgp);

#endif /* _IMAGE_H_ */