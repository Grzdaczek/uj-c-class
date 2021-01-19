#include <stdlib.h>
#include <stdio.h>
#include "err.h"

/*=-------------------------------------------------------------------------=*/

void fail(char* error, char* comment) {
    unsigned char code = 0;
    if (*comment == '\0') {
        printf("spice: error: %s\n", error);
    } 
    else {
        printf("spice: error: %s \"%s\"\n", error, comment);
    }
    while(*error != '\0' && code + *error != 0) { code += *error; error++;}
    exit(code);
}