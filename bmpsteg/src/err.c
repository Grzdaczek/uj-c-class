#include <stdlib.h>
#include <stdio.h>
#include "err.h"

void err(ErrCode code) {
    switch (code) {
        case ERR_NO_ARG:
            printerr("no arguments\n");
            break;
        case ERR_INVALID_CMD:
            printerr("invalid command\n");
            break;
        case ERR_UNSUPORTED_FORMAT:
            printerr("unsuported file format\n");
            break;
        case ERR_UNKNOWN_OPTION:
            printerr("unknown option\n");
            break;
        default:
            printerr("internal\n");
    }
    exit(code);
}