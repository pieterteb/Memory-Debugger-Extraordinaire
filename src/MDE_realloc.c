#include <stdlib.h>

#include "MDE.h"



extern void* MDE_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}
