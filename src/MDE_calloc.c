#include <stdlib.h>


/* This file must not use debug version calloc. */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_memory.h"
#include "MDE_print.h"
#include "MDE_tracker.h"



extern void* MDE_calloc(size_t nmemb, size_t size, const char* file_name, int line_number) {
    MDE_Memory* memory = MDE_memory_new();

    if (!memory) {
        MDE_err(file_name, line_number, "Not enough memory available for MDE.");
        return NULL;
    }

    void* ptr = calloc(nmemb, size);

    if (!(nmemb * size)) {
        MDE_warn(file_name, line_number, "Attempted to calloc memory block of 0 bytes. Implementation-defined behaviour.");
    } else if (!ptr) {
        MDE_warn(file_name, line_number, "Failed to calloc %zu memory block(s) of size %zu.", nmemb, size);
    } else {
        memory->ptr = ptr;
        memory->size = nmemb * size;
        MDE_tracker_add(ptr, file_name, line_number);
    }

    return ptr;
}
