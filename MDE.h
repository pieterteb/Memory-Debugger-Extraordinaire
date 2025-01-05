#ifndef MDE_H
#define MDE_H


#define MDE_DEBUG



#ifdef MDE_DEBUG
    #define malloc(size)        MDE_malloc(size)
    #define calloc(nmemb, size) MDE_calloc(nmemb, size)
    #define realloc(ptr, size)  MDE_realloc(ptr, size)
    
    #define free(ptr)           MDE_free(ptr)
#endif


extern void* MDE_malloc(size_t size);
extern void* MDE_calloc(size_t nmemb, size_t size);
extern void* MDE_realloc(void* ptr, size_t size);

extern void  MDE_free(void* ptr);



#endif
