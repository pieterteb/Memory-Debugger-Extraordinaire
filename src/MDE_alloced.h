#ifndef MDE_ALLOCED_H
#define MDE_ALLOCED_H


#include "MDE.h"



void MDE_alloced_add(void* ptr, size_t size);
void MDE_alloced_remove(void* ptr);
size_t MDE_alloced_count();



#endif /* MDE_ALLOCED_H */
