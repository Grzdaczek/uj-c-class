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
    image_read_ppm(&img, imgin);

    for (i = 0; i < queue_len; i++) {
        ActionDispatcher dispatcher = match_dispatcher(queue[i].argv[0]);
        if (dispatcher) dispatcher(&img, queue[i]);
    }

    image_write_ppm(&img, imgout);
    free(img.data);

    return 0;
}
