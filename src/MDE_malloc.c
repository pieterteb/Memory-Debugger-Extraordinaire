#include <stdlib.h>

#include "MDE.h"



extern void* MDE_malloc(size_t size) {
    return malloc(size);
}
