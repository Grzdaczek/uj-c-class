#include <stdlib.h>
#include <stdio.h>
#include "action.h"
#include "err.h"

int dispatch_null(Image *imgp, ActionParams params) {
    printf("NULL DISPATCHED");
    return 0;
}

int dispatch_tap(Image *imgp, ActionParams params) {
    return image_tap(imgp);
}

int dispatch_invert(Image *imgp, ActionParams params) {
    return image_invert(imgp);
}

ActionArr DISPATCHERS[] = {
    {"-null",    dispatch_null},
    {"-tap",    dispatch_tap},
    {"-invert",    dispatch_invert},
};

ActionDispatcher match_dispatcher(char* label) {
    int i;
    int len = sizeof(DISPATCHERS)/sizeof(ActionArr);
    ActionArr* cur_disp = NULL;

    for (i = 0; i < len; i++) {
        if (!strcmp(DISPATCHERS[i].label, label)) return DISPATCHERS[i].disp;
    }

	err(ERR_INVALID_CMD);
    return NULL;
}