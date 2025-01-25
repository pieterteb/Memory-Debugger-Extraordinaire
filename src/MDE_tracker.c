#include <stdio.h>
#include <stdlib.h>


/* This file must not use debug versions of malloc & friends. */
#define MDE_NO_DEBUG_MEM


#include "MDE.h"
#include "MDE_tracker.h"
#include "MDE_memory.h"
#include "MDE_print.h"



typedef struct MDE_Tracker {
    MDE_Memory**    memories;

    size_t          count;
    size_t          size;
} MDE_Tracker;


#ifdef MDE_DEBUG
static MDE_Tracker mde_tracker_ = { NULL, 0, 0 };
#endif


void MDE_tracker_add(MDE_Memory* memory, const char* file_name, int line_number) {
    if (mde_tracker_.count == mde_tracker_.size) {
        if (!mde_tracker_.size) {
            mde_tracker_.size = 1;
        } else {
            mde_tracker_.size *= 2;
        }

        mde_tracker_.memories = realloc(mde_tracker_.memories, mde_tracker_.size * sizeof(*mde_tracker_.memories));

        if (!mde_tracker_.memories) {
            MDE_err(file_name, line_number, "Not enough memory available for MDE.");
            return;
        }
    }

    mde_tracker_.memories[mde_tracker_.count] = memory;
    ++mde_tracker_.count;
}

void MDE_tracker_remove(void* ptr, const char* file_name, int line_number) {
    size_t i = 0;

    /* Find ptr. */
    for (; i < mde_tracker_.count; ++i) {
        if (ptr == mde_tracker_.memories[i]->ptr) {
            break;
        }
    }

    if (i == mde_tracker_.count) {
        MDE_err(file_name, line_number, "Attempted to free an unallocated, or previously deallocated block of memory, %p. Undefined behaviour.", ptr);
        return;
    }

    MDE_memory_destroy(mde_tracker_.memories[i]);
    --mde_tracker_.count;

    /* Move pointers to fill gap. */
    for (; i < mde_tracker_.count; ++i) {
        mde_tracker_.memories[i] = mde_tracker_.memories[i + 1];
    }
}

void MDE_tracker_set(void* old_ptr, void* new_ptr, size_t new_size, const char* file_name, int line_number) {
    for (size_t i = 0; i < mde_tracker_.count; ++i) {
        if (mde_tracker_.memories[i]->ptr == old_ptr) {
            mde_tracker_.memories[i]->ptr = new_ptr;
            mde_tracker_.memories[i]->size = new_size;
            ++mde_tracker_.memories[i]->times_reallocated;
            return;
        }
    }

    MDE_err(file_name, line_number, "Attempted to reallocate an unallocated, or previously deallocated block of memory, %p. Undefined behaviour.", old_ptr);
}


extern void MDE_tracker_print(FILE* stream) {
    size_t total_size = 0;

    fputs("Address:       | Size (bytes): | Times Reallocated: | Comment:\n", stream);
    fputs("---------------------------------------------------------------\n", stream);
    for (size_t i = 0; i < mde_tracker_.count; ++i) {
        if (mde_tracker_.memories[i]->comment) {
            fprintf(stream, "%13p | %13zu | %18zu | %s\n", mde_tracker_.memories[i]->ptr, mde_tracker_.memories[i]->size, mde_tracker_.memories[i]->times_reallocated, mde_tracker_.memories[i]->comment);
        } else {
            fprintf(stream, "%13p | %13zu | %18zu | N/A\n", mde_tracker_.memories[i]->ptr, mde_tracker_.memories[i]->size, mde_tracker_.memories[i]->times_reallocated);
        }
        total_size += mde_tracker_.memories[i]->size;
    }

    fprintf(stream, "Total count: %zu\n"
           "Total size: %zu\n", 
           mde_tracker_.count, 
           total_size);
}

extern void MDE_tracker_destroy(const char* file_name, int line_number) {
    for (size_t i = 0; i < mde_tracker_.count; ++i) {
        MDE_memory_destroy(mde_tracker_.memories[i]);
    }
    free(mde_tracker_.memories);

    MDE_warn(file_name, line_number, "Destroyed tracker.");
}
