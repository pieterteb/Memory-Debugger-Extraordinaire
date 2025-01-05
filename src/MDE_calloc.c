#include <stdlib.h>

#include "MDE.h"



extern void* MDE_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}
