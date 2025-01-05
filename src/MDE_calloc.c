#include <stdlib.h>


#define MDE_NO_DEBUG


#include "MDE.h"



extern void* MDE_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}
