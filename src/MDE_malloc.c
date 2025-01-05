#include <stdlib.h>


#define MDE_NO_DEBUG


#include "MDE.h"



extern void* MDE_malloc(size_t size) {
    return malloc(size);
}
