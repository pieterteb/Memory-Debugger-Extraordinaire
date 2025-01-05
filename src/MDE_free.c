#include <stdlib.h>

#include "MDE.h"



extern void MDE_free(void* ptr) {
    free(ptr);
}
