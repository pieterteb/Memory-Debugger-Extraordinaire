#include <stdio.h>
#include <stdlib.h>


/* This file must not use debug versions of malloc & friends. */
#define MDE_NO_DEBUG


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
    static MDE_Alloced mde_alloced_ = (MDE_Alloced){ NULL, NULL, 0, 0 };
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

void MDE_alloced_remove(void* ptr) {
    void*  temp_ptr = NULL;
    size_t temp_size = 0;
    for (size_t i = mde_alloced_.count; i != 0;) {
        --i;
        temp_ptr = mde_alloced_.ptrs[i];
        temp_size = mde_alloced_.sizes[i];
        if (ptr == temp_ptr) {
            --mde_alloced_.count;
            return;
        }
        mde_alloced_.ptrs[i] = mde_alloced_.ptrs[i + 1];
        mde_alloced_.sizes[i] = mde_alloced_.sizes[i + 1];
    }

    MDE_err("Attempted to free an unallocated or previously freed block of memory, %p.", ptr);
}

size_t MDE_alloced_count() {
    return mde_alloced_.count;
}
