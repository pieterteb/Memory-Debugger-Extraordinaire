#include <stdarg.h>
#include <stdlib.h>

/* This file must not use debug version of calloc(). */
#define MDE_NO_DEBUG

#include "MDE.h"
#include "MDE_memory.h"
#include "MDE_print.h"
#include "MDE_tracker.h"



extern void* MDE_calloc(size_t nmemb, size_t size, const char* file_name, int line_number) {
    MDE_Memory* memory = MDE_memory_new();

    if (!memory) {
        MDE_err(file_name, line_number, "Not enough memory available for MDE tracker.");
        return NULL;
    }

    if (!(nmemb * size)) {
        MDE_warn(file_name, line_number, "Attempted to calloc memory block of 0 bytes. Implementation-defined behaviour.");
    }

    void* ptr = calloc(nmemb, size);

    if (!ptr) {
        MDE_warn(file_name, line_number, "Failed to calloc %zu memory block(s) of size %zu.", nmemb, size);
    } else {
        memory->ptr = ptr;
        memory->size = nmemb * size;
        MDE_tracker_add(memory, file_name, line_number);
    }

    return ptr;
}

extern void* MDE_calloc_comment(size_t nmemb, size_t size, const char* file_name, int line_number, const char* formatted_comment, ...) {
    if (!formatted_comment) {
        return MDE_calloc(nmemb, size, file_name, line_number);
    }

    MDE_Memory* memory = MDE_memory_new();

    if (!memory) {
        MDE_err(file_name, line_number, "Not enough memory available for MDE tracker.");
        return NULL;
    }

    if (!(nmemb * size)) {
        MDE_warn(file_name, line_number, "Attempted to calloc memory block of 0 bytes. Implementation-defined behaviour.");
    }

    void* ptr = calloc(nmemb, size);

    if (!ptr) {
        MDE_warn(file_name, line_number, "Failed to calloc %zu memory block(s) of size %zu.", nmemb, size);
    } else {
        memory->ptr = ptr;
        memory->size = nmemb * size;

        va_list args;

        va_start(args, formatted_comment);
        MDE_memory_set_comment(memory, file_name, line_number, formatted_comment, args);
        va_end(args);

        MDE_tracker_add(memory, file_name, line_number);
    }

    return ptr;
}
