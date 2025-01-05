#include <stdlib.h>


/* This file must not use debug version of free(). */
#define MDE_NO_DEBUG


#include "MDE.h"



extern void MDE_free(void* ptr) {
    free(ptr);
}
