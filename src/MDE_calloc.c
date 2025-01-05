#include <stdlib.h>


/* This file must not use debug version calloc. */
#define MDE_NO_DEBUG


#include "MDE.h"



extern void* MDE_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}
