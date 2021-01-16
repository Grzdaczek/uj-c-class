#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "err.h"

#define OPTION_IN "-i"
#define OPTION_OUT "-o"
#define OPTION_ACTION "-a"

void print_help() {
    
    printf("OPTIONS:\n");
    printf("  -i <file>\t\tPath to input image file, defaults to stdin\n");
    printf("  -o <file>\t\tPath to output image file, defaults to stdout\n");
    printf("  -a <ACTION> [<PARAM>]\tEnqeue action with list of parameters, \n\t\t\tfor ex. \"-a rotate 90\" etc.\n");
    printf("  -h \t\tPrint help\n");

    printf("ACTIONS:\n");
    printf("  invert\t\tInvert colors\n");
    // ...

    exit(0);
}

//#=---------------------------------------------------------------------------

typedef struct {
    int argc;
    char** argv;
} ActionParams;

typedef struct {
    const char* label;
    int (*dispatch)(int argc, char** argv);
} ActionDispatcher;

int dispatch_null(int argc, char** argv) {
    printf("NULL DISPATCHED");
    return 0;
}

const ActionDispatcher DISPATCHERS[] = {
    {"null",    dispatch_null}
};

ActionDispatcher* match_dispatcher(char* label) {
    if(label[0] != '-') return NULL;
    int i;
    int len = sizeof(DISPATCHERS)/sizeof(ActionDispatcher);
    ActionDispatcher* cur_disp = NULL;

    for (i = 0; i < len; i++) {
        cur_disp = &DISPATCHERS[i];
        if (!strcmp(cur_disp->label, label)) return &DISPATCHERS[i];
    }

    return NULL;
}

int main(int argc, char** argv) {
    int i, j, k;

    FILE *imgin = stdin;
    FILE *imgout = stdout;

    char* curr_arg = NULL;

    
    return 0;
}

//#=---------------------------------------------------------------------------
/*
typedef struct {
    const char* prefix;
    int (*dispatch)(int argc, char** argv);
} OptionDispatcher;

typedef struct {
    OptionDispatcher* dispatcher;
    int argc;
    char** argv;
} Option;

int dispatch_input_option (int argc, char** argv) {
    printf("INPUT DISPATCHED!\n");
    return 0;
}

FILE* imgin = NULL;
FILE* imgout = NULL;
OptionDispatcher DISPATCHERS[] = {
    {"-i",      dispatch_input_option},
};

OptionDispatcher* match_dispatcher(char* prefix) {
    if(prefix[0] != '-') return NULL;
    int i;
    int len = sizeof(DISPATCHERS)/sizeof(OptionDispatcher);
    OptionDispatcher* cur_disp = NULL;

    for (i = 0; i < len; i++) {
        cur_disp = &DISPATCHERS[i];
        if (!strcmp(cur_disp->prefix, prefix)) return &DISPATCHERS[i];
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    int i, j, k;
    int option_size = 0;
    Option option_vals[256];
    Option* cur_option = NULL;
    OptionDispatcher *cur_disp = NULL;

    for (i = 1; i < argc; i++) {            
        if ((cur_disp = match_dispatcher(argv[i]))) {
            cur_option = &option_vals[option_size];
            cur_option->dispatcher = cur_disp;
            cur_option->argv = &argv[i];
            cur_option->argc = 0;
            option_size += 1;
        }
        else if (argv[i][0] == '-') err(ERR_UNKNOWN_OPTION);
        else if (cur_option) cur_option->argc += 1;
    }

    imgin = stdin;
    imgout = stdout;

    printf("%d\n", option_size);

    for (i = 0; i < option_size; i++) {
        cur_option = &option_vals[i];
        cur_option->dispatcher->dispatch(cur_option->argc, cur_option->argv);
    }

    // FILE *i_imgf = fopen(i_imgp, "rb");
    // FILE *o_datf = o_datp ? fopen(o_datp, "rb") : stdout;
    // Image *img = read_image(i_imgf);

    return 0;
}
*/

