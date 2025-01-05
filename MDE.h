#ifndef MDE_H
#define MDE_H


#include <stdio.h>



#define MDE_DEBUG



#if defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG)
    #define malloc(size)        MDE_malloc(size)
    #define calloc(nmemb, size) MDE_calloc(nmemb, size)
    #define realloc(ptr, size)  MDE_realloc(ptr, size)
    
    #define free(ptr)           MDE_free(ptr)
#endif


extern void* MDE_malloc(size_t size);
extern void* MDE_calloc(size_t nmemb, size_t size);
extern void* MDE_realloc(void* ptr, size_t size);

extern void MDE_free(void* ptr);

extern void MDE_alloced_print(FILE* stream);



#endif /* MDE_H */
