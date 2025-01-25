#include <stdlib.h>


/* This file must not use debug versions of malloc & friends. */
#define MDE_NO_DEBUG_MEM


#include "MDE_memory.h"



MDE_Memory* MDE_memory_new() {
    MDE_Memory* memory = malloc(sizeof(*memory));

    if (memory) {
        memory->ptr = NULL;
        memory->size = 0;
        memory->comment = NULL;
        memory->times_reallocated = 0;
    }

    return memory;
}

void MDE_memory_destroy(MDE_Memory* memory) {
    free(memory->comment);
    free(memory);
}
