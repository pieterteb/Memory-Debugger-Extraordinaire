#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "MDE.h"
#include "MDE_print.h"



static void MDE_message(const char* file_name, int line_number);


static void MDE_message(const char* file_name, int line_number) {
    fprintf(stderr, "MDE (File:%s, Line:%d): ", file_name, line_number);
}

void MDE_warn(const char* file_name, int line_number, char* warning, ...) {
    MDE_message(file_name, line_number);
    fprintf(stderr, "WARNING - ");

    va_list args;
    va_start(args, warning);

    vfprintf(stderr, warning, args);

    va_end(args);

    fputc('\n', stderr);

#ifdef MDE_EXIT_AT_WARNING
    MDE_tracker_destroy();
    exit(EXIT_FAILURE);
#endif /* MDE_EXIT_AT_WARNING */
}

void MDE_err(const char* file_name, int line_number, char* error, ...) {
    MDE_message(file_name, line_number);
    fprintf(stderr, "ERROR - ");

    va_list args;
    va_start(args, error);

    vfprintf(stderr, error, args);

    va_end(args);

    fputc('\n', stderr);

#ifdef MDE_EXIT_AT_ERROR
    MDE_tracker_destroy();
    exit(EXIT_FAILURE);
#endif /* MDE_EXIT_AT_ERROR */
}
