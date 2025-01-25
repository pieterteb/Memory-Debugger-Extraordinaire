#include <stdio.h>
#include <stdlib.h>


/* This file must not use debug versions of malloc & friends. */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_memory.h"
#include "MDE_print.h"



typedef struct {
    MDE_Memory**    memories;

    size_t          count;
    size_t          size;
} MDE_Alloced;


#ifdef MDE_DEBUG
static MDE_Alloced mde_alloced_ = { NULL, 0, 0 };
#endif


void MDE_alloced_add(MDE_Memory* memory, const char* file_name, int line_number) {
    if (mde_alloced_.count == mde_alloced_.size) {
        if (!mde_alloced_.size) {
            mde_alloced_.size = 1;
        } else {
            mde_alloced_.size *= 2;
        }

        mde_alloced_.memories = realloc(mde_alloced_.memories, mde_alloced_.size * sizeof(*mde_alloced_.memories));

        if (!mde_alloced_.memories) {
            MDE_err(file_name, line_number, "Not enough memory available for MDE.");
            return;
        }
    }

    mde_alloced_.memories[mde_alloced_.count] = memory;
    ++mde_alloced_.count;
}

void MDE_alloced_remove(void* ptr, const char* file_name, int line_number) {
    size_t i = 0;

    /* Find ptr. */
    for (; i < mde_alloced_.count; ++i) {
        if (ptr == mde_alloced_.memories[i]->ptr) {
            break;
        }
    }

    if (i == mde_alloced_.count) {
        MDE_err(file_name, line_number, "Attempted to free an unallocated, or previously deallocated block of memory, %p. Undefined behaviour.", ptr);
        return;
    }

    MDE_memory_destroy(mde_alloced_.memories[i]);
    --mde_alloced_.count;

    /* Move pointers to fill gap. */
    for (; i < mde_alloced_.count; ++i) {
        mde_alloced_.memories[i] = mde_alloced_.memories[i + 1];
    }
}

void MDE_alloced_set(void* old_ptr, void* new_ptr, size_t new_size, const char* file_name, int line_number) {
    for (size_t i = 0; i < mde_alloced_.count; ++i) {
        if (mde_alloced_.memories[i]->ptr == old_ptr) {
            mde_alloced_.memories[i]->ptr = new_ptr;
            mde_alloced_.memories[i]->size = new_size;
            ++mde_alloced_.memories[i]->times_reallocated;
            return;
        }
    }

    MDE_err(file_name, line_number, "Attempted to reallocate an unallocated, or previously deallocated block of memory, %p. Undefined behaviour.", old_ptr);
}


extern void MDE_print_table(FILE* stream) {
    size_t total_size = 0;

    fputs("Address:       | Size (bytes): | Times Reallocated: | Comment:\n", stream);
    fputs("---------------------------------------------------------------\n", stream);
    for (size_t i = 0; i < mde_alloced_.count; ++i) {
        if (mde_alloced_.memories[i]->comment) {
            fprintf(stream, "%p | %zu | %zu | %s\n", mde_alloced_.memories[i]->ptr, mde_alloced_.memories[i]->size, mde_alloced_.memories[i]->times_reallocated, mde_alloced_.memories[i]->comment);
        } else {
            fprintf(stream, "%p | %zu | %zu | N/A\n", mde_alloced_.memories[i]->ptr, mde_alloced_.memories[i]->size, mde_alloced_.memories[i]->times_reallocated);
        }
        total_size += mde_alloced_.memories[i]->size;
    }

    fprintf(stream, "Total count: %zu\n"
           "Total size: %zu\n", 
           mde_alloced_.count, 
           total_size);
}

extern void MDE_destroy(const char* file_name, int line_number) {
    for (size_t i = 0; i < mde_alloced_.count; ++i) {
        MDE_memory_destroy(mde_alloced_.memories[i]);
    }
    free(mde_alloced_.memories);

    MDE_warn(file_name, line_number, "Destroyed alloced.");
}
