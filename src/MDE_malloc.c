#include <stdlib.h>


/* This file must not use debug version of malloc(). */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_memory.h"
#include "MDE_print.h"



extern void* MDE_malloc(size_t size, const char* file_name, int line_number) {
    MDE_Memory* memory = MDE_memory_new();

    if (!memory) {
        MDE_err(file_name, line_number, "Not enough memory available for MDE.");
        return NULL;
    }

    void* ptr = malloc(size);

    if (!size) {
        MDE_warn(file_name, line_number, "Attempted to malloc memory block of 0 bytes. Implementation-defined behaviour.");
    } else if (!ptr) {
        MDE_warn(file_name, line_number, "Failed to malloc memory block of size %zu.", size);
    } else {
        memory->ptr = ptr;
        memory->size = size;
        MDE_alloced_add(memory, file_name, line_number);
    }

    return ptr;
}
