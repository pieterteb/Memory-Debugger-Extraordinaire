#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


/* This file must not use debug versions of malloc & friends. */
#define MDE_NO_DEBUG_MEM


#include "MDE_memory.h"
#include "MDE_print.h"



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

void MDE_memory_set_comment(MDE_Memory* memory, const char* file_name, int line_number, const char* formatted_comment, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);

    int comment_length = vsnprintf(NULL, 0, formatted_comment, args_copy);
    va_end(args_copy);

    if (comment_length < 0) {
        MDE_warn(file_name, line_number, "Failed to add comment to pointer %p. It is possible the formatted string does not match the given arguments.");
    } else {
        memory->comment = realloc(memory->comment, (comment_length + 1) * sizeof(*memory->comment));

        if (memory->comment) {
            vsnprintf(memory->comment, comment_length + 1, formatted_comment, args);
        } else {
            MDE_warn(file_name, line_number, "Not enough memory available for MDE tracker comment.");
        }
    }
}
