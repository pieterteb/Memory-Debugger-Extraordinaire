#include <stdlib.h>


/* This file must not use debug version of free(). */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"



extern void MDE_free(void* ptr, const char* file_name, int line_number) {
    if (ptr) {
        MDE_alloced_remove(ptr, file_name, line_number);
        free(ptr);
    }
}
