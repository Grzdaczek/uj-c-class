#ifndef _ERR_H_
#define _ERR_H_

#define PROG_NAME "ppmsteg"
#define printerr(string) fprintf(stderr, PROG_NAME": error: "string)

#define READ_ACTION "read"
#define WRITE_ACTION "write"

typedef enum {
    ERR_GENERIC,
    ERR_NO_ARG,
    ERR_INVALID_CMD,
    ERR_UNSUPORTED_FORMAT,
    ERR_UNKNOWN_OPTION,
    ERR_NO_OPTION,
} ErrCode;

void err(ErrCode code);

#endif /* _ERR_H */