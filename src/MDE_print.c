#include <stdio.h>

#include "MDE_print.h"



static void MDE_message();


static void MDE_message() {
    fprintf(stderr, "MDE: ");
}

void MDE_warn(char* warning) {
    MDE_message();

    fprintf(stderr, "Warning - %s\n", warning);
}

void MDE_err(char* error) {
    MDE_message();

    fprintf(stderr, "ERROR - %s", error);
}
