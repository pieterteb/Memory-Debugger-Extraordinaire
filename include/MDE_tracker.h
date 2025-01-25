#ifndef MDE_TRACKER_H
#define MDE_TRACKER_H


#include <stddef.h>

#include "MDE_memory.h"



void MDE_tracker_add(MDE_Memory* memory, const char* file_name, int line_number);
void MDE_tracker_remove(void* ptr, const char* file_name, int line_number);
void MDE_tracker_set(void* old_ptr, void* new_ptr, size_t new_size, const char* file_name, int line_number);



#endif /* MDE_TRACKER_H */
