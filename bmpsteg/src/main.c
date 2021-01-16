#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "action.h"
#include "err.h"

void print_help() {

    printf("OPTIONS:\n");
    printf("  -i <file>\t\tPath to input image file, defaults to stdin\n");
    printf("  -o <file>\t\tPath to output image file, defaults to stdout\n");
    printf("  -a <ACTION> [<PARAM>]\tEnqeue action with list of parameters, \n\t\t\tfor ex. \"-a rotate 90\" etc.\n");
    printf("  -h \t\tPrint help\n");

    printf("ACTIONS:\n");
    printf("  invert\t\tInvert colors\n");

    exit(0);
}

/*=-------------------------------------------------------------------------=*/

int read_ppm(FILE* imgin, Image* imgp) {
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

int write_ppm(FILE* imgout, Image* imgp) {
    fprintf(imgout, "P6\n");
    fprintf(imgout, "%d %d\n", imgp->width, imgp->height);
    fprintf(imgout, "%d\n", imgp->bitdepth);
    fwrite(imgp->data, imgp->data_size, sizeof(Pixel), imgout);
    return 0;
}

int main(int argc, char** argv) {
    int i, j, k;
    char* curr_arg = NULL;
    int queue_len = 0;
    ActionParams queue[256];
    FILE *imgin = stdin;
    FILE *imgout = stdout;

    /* TEMP SOLUTION */
    if (argc < 5) err(ERR_GENERIC);
    imgin = fopen(argv[2], "rb");
    imgout = fopen(argv[4], "wb");

    for (i = 5; i < argc; i++) {
        if (argv[i][0] == '-') {
            queue_len += 1;
            queue[queue_len-1].argc = 1;
            queue[queue_len-1].argv = &argv[i];
        }
        else {
            queue[queue_len-1].argc += 1;
        }
    }

    Image img;
    img.data = NULL;
    read_ppm(imgin, &img);

    for (i = 0; i < queue_len; i++) {
        ActionDispatcher dispatcher = match_dispatcher(queue[i].argv[0]);
        if (dispatcher) dispatcher(&img, queue[i]);
        printf("%s\n", queue[i].argv[0]);
    }

    write_ppm(imgout, &img);

    return 0;
}
