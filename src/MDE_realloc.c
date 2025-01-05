#include <stdlib.h>


/* This file must n ot use debug version of realloc(). */
#define MDE_NO_DEBUG


#include "MDE.h"



extern void* MDE_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}
