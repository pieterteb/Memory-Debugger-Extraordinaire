#include <stdlib.h>


/* This file must n ot use debug version of realloc(). */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_print.h"



extern void* MDE_realloc(void* ptr, size_t size, const char* file_name, int line_number) {
    void* new_ptr = realloc(ptr, size);

    if (!size) {
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >=  202311L
        MDE_err(file_name, line_number, "Attempted to realloc to memory block of 0 bytes. Undefined behaviour.");
#else
        MDE_warn(file_name, line_number, "Attempted to realloc to memory block of 0 bytes. Implementation-defined behaviour.");
#endif /* __STDC_VERSION__ >=  202311L */
    } else if (!new_ptr) {
        MDE_warn(file_name, line_number, "Failed to realloc memory block at %p to size %zu.", ptr, size);
        new_ptr = ptr;
    } else {
        MDE_alloced_set(ptr, new_ptr, size, file_name, line_number);
    }

    return new_ptr;
}
