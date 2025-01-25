#ifndef MDE_MEMORY_H
#define MDE_MEMORY_H


#include <stddef.h>



typedef struct MDE_Memory {
    void*   ptr;
    size_t  size;
    char*   comment;
    size_t  times_reallocated;
} MDE_Memory;


MDE_Memory* MDE_memory_new();

void MDE_memory_destroy(MDE_Memory* memory);



#endif /* MDE_MEMORY_H */
