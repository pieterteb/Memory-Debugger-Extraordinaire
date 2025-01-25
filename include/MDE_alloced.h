#ifndef MDE_ALLOCED_H
#define MDE_ALLOCED_H


void MDE_alloced_add(void* ptr, size_t size);
void MDE_alloced_remove(void* ptr);
void MDE_alloced_set(void** old_ptr, void* new_ptr, size_t new_size);

size_t MDE_alloced_count();



#endif /* MDE_ALLOCED_H */
