#ifndef MDE_H
#define MDE_H


#include <stdio.h>



#define MDE_DEBUG



#if defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG_MEM)
    #define malloc(size)        MDE_malloc(size)
    #define calloc(nmemb, size) MDE_calloc(nmemb, size)
    #define realloc(ptr, size)  MDE_realloc(ptr, size)
    
    #define free(ptr)           MDE_free(ptr)
#endif /* defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG_MEM) */


/**
 * @brief MDE extension of malloc(). Behaves like malloc(), but checks if @a size is 0, or allocation failed.
 * 
 * @param size Number of bytes to allocate.
 * @return void* 
 */
extern void* MDE_malloc(size_t size);

/**
 * @brief MDE extension of calloc(). Behaves like calloc(), but checks if @a nmemb * @a size is 0, or allocation failed.
 * 
 * @param nmemb Number of objects.
 * @param size Size of each object.
 * @return void* 
 */
extern void* MDE_calloc(size_t nmemb, size_t size);

/**
 * @brief MDE extension of realloc(). Behaves like realloc(), but checks if @a size is 0, or reallocation failed. 
 * 
 * @param ptr Pointer to the memory area to be reallocated.
 * @param size New size of the array in bytes.
 * @return void* 
 */
extern void* MDE_realloc(void* ptr, size_t size);

/**
 * @brief MDE extension of free(). Behaves like free(), but checks if memory has never been allocated and, or has been deallocated before.
 * 
 * @param ptr Pointer to the memory to deallocate.
 */
extern void MDE_free(void* ptr);


/**
 * @brief Prints table of currently allocated memory addresses and sizes.
 * 
 * @param stream Output stream to print to.
 */
extern void MDE_print_table(FILE* stream);

/**
 * @brief Deallocates all memory used by MDE.
 * 
 */
extern void MDE_destroy();



#endif /* MDE_H */
