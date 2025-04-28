#include <stdarg.h>
#include <stdlib.h>

/* This file must not use debug version of malloc(). */
#define MDE_NO_DEBUG

#include "MDE.h"
#include "MDE_memory.h"
#include "MDE_print.h"
#include "MDE_tracker.h"



extern void* MDE_malloc(size_t size, const char* file_name, int line_number) {
    MDE_Memory* memory = MDE_memory_new();

    if (!memory) {
        MDE_err(file_name, line_number, "Not enough memory available for MDE tracker.");
        return NULL;
    }

    if (!size) {
        MDE_warn(file_name, line_number, "Attempted to malloc memory block of 0 bytes. Implementation-defined behaviour.");
    }

    void* ptr = malloc(size);

    if (!ptr) {
        MDE_warn(file_name, line_number, "Failed to malloc memory block of size %zu.", size);
    } else {
        memory->ptr = ptr;
        memory->size = size;
        MDE_tracker_add(memory, file_name, line_number);
    }

    return ptr;
}

extern void* MDE_malloc_comment(size_t size, const char* file_name, int line_number, const char* formatted_comment, ...) {
    if (!formatted_comment) {
        return MDE_malloc(size, file_name, line_number);
    }

    MDE_Memory* memory = MDE_memory_new();

    if (!memory) {
        MDE_err(file_name, line_number, "Not enough memory available for MDE tracker.");
        return NULL;
    }

    if (!size) {
        MDE_warn(file_name, line_number, "Attempted to malloc memory block of 0 bytes. Implementation-defined behaviour.");
    }

    void* ptr = malloc(size);

    if (!ptr) {
        MDE_warn(file_name, line_number, "Failed to malloc memory block of size %zu.", size);
    } else {
        memory->ptr = ptr;
        memory->size = size;

        va_list args;

        va_start(args, formatted_comment);
        MDE_memory_set_comment(memory, file_name, line_number, formatted_comment, args);
        va_end(args);

        MDE_tracker_add(memory, file_name, line_number);
    }

    return ptr;
}
