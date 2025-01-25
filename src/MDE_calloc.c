#include <stdlib.h>


/* This file must not use debug version calloc. */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_print.h"



extern void* MDE_calloc(size_t nmemb, size_t size) {
    void* ptr = calloc(nmemb, size);

    if (!ptr) {
        MDE_warn("Failed to calloc %zu memory block(s) of size %zu.", nmemb, size);
    } else {
        MDE_alloced_add(ptr, nmemb * size);
    }

    return ptr;
}
