#include <stdlib.h>


/* This file must not use debug version of malloc(). */
#define MDE_NO_DEBUG


#include "MDE.h"



extern void* MDE_malloc(size_t size) {
    return malloc(size);
}
