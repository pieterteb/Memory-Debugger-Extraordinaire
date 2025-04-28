#include <stdlib.h>

/* This file must not use debug version of realloc(). */
#define MDE_NO_DEBUG

#include "MDE.h"
#include "MDE_print.h"
#include "MDE_tracker.h"



extern void* MDE_realloc(void* ptr, size_t size, const char* file_name, int line_number) {
    if (!size) {
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >=  202311L
        MDE_err(file_name, line_number, "Attempted to realloc to memory block of 0 bytes. Undefined behaviour.");
#else
        MDE_warn(file_name, line_number, "Attempted to realloc to memory block of 0 bytes. Implementation-defined behaviour.");
#endif /* __STDC_VERSION__ >=  202311L */
    }

    void* new_ptr = realloc(ptr, size);

    if (!new_ptr) {
        MDE_warn(file_name, line_number, "Failed to realloc memory block at %p to size %zu.", ptr, size);
        new_ptr = ptr;
    } else {
        MDE_tracker_set(ptr, new_ptr, size, file_name, line_number);
    }

    return new_ptr;
}

extern void* MDE_realloc_comment(void* ptr, size_t size, const char* file_name, int line_number, const char* formatted_comment, ...) {
    if (!formatted_comment) {
        return MDE_realloc(ptr, size, file_name, line_number);
    }

    if (!size) {
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >=  202311L
        MDE_err(file_name, line_number, "Attempted to realloc to memory block of 0 bytes. Undefined behaviour.");
#else
        MDE_warn(file_name, line_number, "Attempted to realloc to memory block of 0 bytes. Implementation-defined behaviour.");
#endif /* __STDC_VERSION__ >=  202311L */
    }

    void* new_ptr = realloc(ptr, size);

    if (!new_ptr) {
        MDE_warn(file_name, line_number, "Failed to realloc memory block at %p to size %zu.", ptr, size);
        new_ptr = ptr;
    } else {
        va_list args;

        va_start(args, formatted_comment);
        MDE_tracker_set_comment(ptr, new_ptr, size, file_name, line_number, formatted_comment, args);
        va_end(args);
    }

    return new_ptr;
}
