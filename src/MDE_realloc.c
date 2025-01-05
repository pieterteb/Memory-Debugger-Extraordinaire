#include <stdlib.h>


#define MDE_NO_DEBUG


#include "MDE.h"



extern void* MDE_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}
