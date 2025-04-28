#include <stdlib.h>

/* This file must not use debug version of free(). */
#define MDE_NO_DEBUG

#include "MDE.h"
#include "MDE_tracker.h"



extern void MDE_free(void* ptr, const char* file_name, int line_number) {
    if (ptr) {
        MDE_tracker_remove(ptr, file_name, line_number);
        free(ptr);
    }
}
