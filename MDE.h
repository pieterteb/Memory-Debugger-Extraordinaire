#ifndef MDE_H
#define MDE_H


#include <stdio.h>



/* If defined, MDE versions of malloc and friends will be used. */
#define MDE_DEBUG


/**
 * @brief MDE extension of malloc(). Behaves like malloc(), but checks if @a size is 0, or allocation failed.
 * 
 * @param size Number of bytes to allocate.
 * @return void* 
 */
extern void* MDE_malloc(size_t size, const char* file_name, int line_number);

/**
 * @brief MDE extension of calloc(). Behaves like calloc(), but checks if @a nmemb * @a size is 0, or allocation failed.
 * 
 * @param nmemb Number of objects.
 * @param size Size of each object.
 * @return void* 
 */
extern void* MDE_calloc(size_t nmemb, size_t size, const char* file_name, int line_number);

/**
 * @brief MDE extension of realloc(). Behaves like realloc(), but checks if @a size is 0, or reallocation failed. 
 * 
 * @param ptr Pointer to the memory area to be reallocated.
 * @param size New size of the array in bytes.
 * @return void* 
 */
extern void* MDE_realloc(void* ptr, size_t size, const char* file_name, int line_number);

/**
 * @brief MDE extension of free(). Behaves like free(), but checks if memory has never been allocated and, or has been deallocated before.
 * 
 * @param ptr Pointer to the memory to deallocate.
 */
extern void MDE_free(void* ptr, const char* file_name, int line_number);


/**
 * @brief Prints table of currently allocated memory addresses and sizes.
 * 
 * @param stream Output stream to print to.
 */
extern void MDE_tracker_print(FILE* stream);

/**
 * @brief Deallocates all memory used by MDE.
 * 
 */
extern void MDE_tracker_destroy(const char* file_name, int line_number);


#ifndef MDE_NO_DEBUG_MEM
#   define MDE_malloc(size)         MDE_malloc((size), __FILE__, __LINE__)
#   define MDE_calloc(nmemb, size)  MDE_calloc((nmemb), (size), __FILE__, __LINE__)
#   define MDE_realloc(ptr, size)   MDE_realloc((ptr), (size), __FILE__, __LINE__)
#   define MDE_free(ptr)            MDE_free((ptr), __FILE__, __LINE__)

#   define MDE_tracker_destroy()    MDE_tracker_destroy(__FILE__, __LINE__)
#endif /* MDE_NO_DEBUG_MEM */

#if defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG_MEM)
#   define malloc(size)             MDE_malloc((size))
#   define calloc(nmemb, size)      MDE_calloc((nmemb), (size))
#   define realloc(ptr, size)       MDE_realloc((ptr), (size))
#   define free(ptr)                MDE_free((ptr))
#endif /* defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG_MEM) */



#endif /* MDE_H */
