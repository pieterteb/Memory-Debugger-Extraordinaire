#include <stdlib.h>


/* This file must n ot use debug version of realloc(). */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_print.h"



extern void* MDE_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);

    if (!new_ptr) {
        MDE_warn("Failed to realloc memory block at %p to size %zu.", ptr, size);
        new_ptr = ptr;
    } else {
        MDE_alloced_set(ptr, new_ptr, size);
    }

    return new_ptr;
}
