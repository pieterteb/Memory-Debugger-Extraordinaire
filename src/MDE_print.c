#include <stdarg.h>
#include <stdio.h>

#include "MDE_print.h"



static void MDE_message();


static void MDE_message() {
    fprintf(stderr, "MDE: ");
}

void MDE_warn(char* warning, ...) {
    MDE_message();
    fprintf(stderr, "WARNING - ");

    va_list args;
    va_start(args, warning);

    vfprintf(stderr, warning, args);

    va_end(args);

    fputc('\n', stderr);
}

void MDE_err(char* error, ...) {
    MDE_message();
    fprintf(stderr, "ERROR - ", error);

    va_list args;
    va_start(args, error);

    vfprintf(stderr, error, args);

    va_end(args);

    fputc('\n', stderr);
}
