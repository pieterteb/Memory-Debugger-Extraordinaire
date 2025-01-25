#include <stdlib.h>


/* This file must not use debug version of malloc(). */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_print.h"



extern void* MDE_malloc(size_t size) {
    void* ptr = malloc(size);

    if (!size) {
        MDE_warn("Attempted to malloc memory block of 0 bytes.");
    } else if (!ptr) {
        MDE_warn("Failed to malloc memory block of size %zu.", size);
    } else {
        MDE_alloced_add(ptr, size);
    }

    return ptr;
}
