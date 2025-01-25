#include <stdio.h>
#include <stdlib.h>


/* This file must not use debug versions of malloc & friends. */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_alloced.h"
#include "MDE_print.h"



typedef struct {
    void**  ptrs;
    size_t* sizes;

    size_t  count;
    size_t  size;
} MDE_Alloced;


#ifdef MDE_DEBUG
static MDE_Alloced mde_alloced_ = { NULL, NULL, 0, 0 };
#endif


void MDE_alloced_add(void* ptr, size_t size) {
    if (mde_alloced_.count == mde_alloced_.size) {
        if (!mde_alloced_.size) {
            mde_alloced_.size = 1;
        } else {
            mde_alloced_.size *= 2;
        }

        mde_alloced_.ptrs = realloc(mde_alloced_.ptrs, mde_alloced_.size * (sizeof *mde_alloced_.ptrs));
        mde_alloced_.sizes = realloc(mde_alloced_.sizes, mde_alloced_.size * (sizeof *mde_alloced_.sizes));
    }

    mde_alloced_.ptrs[mde_alloced_.count] = ptr;
    mde_alloced_.sizes[mde_alloced_.count] = size;
    ++mde_alloced_.count;
}

void MDE_alloced_remove(void* ptr, const char* file_name, int line_number) {
    size_t i = 0;

    /* Find ptr. */
    for (; i < mde_alloced_.count; ++i) {
        if (ptr == mde_alloced_.ptrs[i]) {
            break;
        }
    }

    if (i == mde_alloced_.count) {
        MDE_err(file_name, line_number, "Attempted to free an unallocated, or previously deallocated block of memory, %p. Undefined behaviour.", ptr);
        return;
    }

    --mde_alloced_.count;

    /* Move pointers to fill gap. */
    for (; i < mde_alloced_.count; ++i) {
        mde_alloced_.ptrs[i] = mde_alloced_.ptrs[i + 1];
        mde_alloced_.sizes[i] = mde_alloced_.sizes[i + 1];
    }
}

void MDE_alloced_set(void* old_ptr, void* new_ptr, size_t new_size, const char* file_name, int line_number) {
    for (size_t i = 0; i < mde_alloced_.count; ++i) {
        if (mde_alloced_.ptrs[i] == old_ptr) {
            mde_alloced_.ptrs[i] = new_ptr;
            mde_alloced_.sizes[i] = new_size;
            return;
        }
    }

    MDE_err(file_name, line_number, "Attempted to reallocate an unallocated, or previously deallocated block of memory, %p. Undefined behaviour.", old_ptr);
}


extern void MDE_print_table(FILE* stream) {
    size_t total_size = 0;

    fputs("Address:       | Size (bytes):\n", stream);
    fputs("-------------------------------\n", stream);
    for (size_t i = 0; i < mde_alloced_.count; ++i) {
        fprintf(stream, "%p | %zu\n", mde_alloced_.ptrs[i], mde_alloced_.sizes[i]);
        total_size += mde_alloced_.sizes[i];
    }

    fprintf(stream, "Total count: %zu\n"
           "Total size: %zu\n", 
           mde_alloced_.count, 
           total_size);
}

extern void MDE_destroy(const char* file_name, int line_number) {
    free(mde_alloced_.ptrs);
    free(mde_alloced_.sizes);

    MDE_warn(file_name, line_number, "Destroyed alloced.");
}
