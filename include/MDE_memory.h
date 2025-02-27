#ifndef MDE_MEMORY_H
#define MDE_MEMORY_H


#include <stdarg.h>
#include <stddef.h>



typedef struct MDE_Memory {
    void*   ptr;
    size_t  size;
    char*   comment;
    size_t  times_reallocated;
} MDE_Memory;


MDE_Memory* MDE_memory_new(const char* file_name, int line_number);

void MDE_memory_destroy(MDE_Memory* memory);

void MDE_memory_set_comment(MDE_Memory* memory, const char* file_name, int line_number, const char* formatted_comment, va_list args);



#endif /* MDE_MEMORY_H */
