#include <stdlib.h>


#define MDE_NO_DEBUG


#include "MDE.h"



extern void MDE_free(void* ptr) {
    free(ptr);
}
