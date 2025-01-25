#ifndef MDE_H
#define MDE_H


#include <stdio.h>



/* If defined, MDE versions of malloc and friends will be used. */
#define MDE_DEBUG

/* If defined, MDE will call MDE_tracker_destroy() and terminate the running program immediately if a warning or an error is encountered respectively. */
// #define MDE_EXIT_AT_WARNING
// #define MDE_EXIT_AT_ERROR


/**
 * @brief MDE extension of malloc(). Behaves like malloc(), but checks if @a size is 0, or allocation failed. Returns NULL if not enough memory for MDE is available.
 * 
 * @param size Number of bytes to allocate.
 * @param file_name Name of file in which MDE_malloc() was called.
 * @param line_number Number of line in @a file_name on which MDE_malloc() was called.
 * @return void* 
 */
extern void* MDE_malloc(size_t size, const char* file_name, int line_number);

/**
 * @brief Same as MDE_malloc(), but allows the user to set a comment as metadata for the allocated memory block. If @a formatted_comment is NULL, no comment is added.
 * 
 * @param size Number of bytes to allocate.
 * @param file_name Name of file in which MDE_malloc_comment() was called.
 * @param line_number Number of line in @a file_name on which MDE_malloc_comment() was called.
 * @param formatted_comment Formatted string.
 * @param ... Arguments for @a formatted_comment.
 * @return void* 
 */
extern void* MDE_malloc_comment(size_t size, const char* file_name, int line_number, const char* formatted_comment, ...);

/**
 * @brief MDE extension of calloc(). Behaves like calloc(), but checks if @a nmemb * @a size is 0, or allocation failed. Returns NULL if not enough memory for MDE is available.
 * 
 * @param nmemb Number of objects.
 * @param size Size of each object.
 * @param file_name Name of file in which MDE_calloc() was called.
 * @param line_number Number of line in @a file_name on which MDE_calloc() was called.
 * @return void* 
 */
extern void* MDE_calloc(size_t nmemb, size_t size, const char* file_name, int line_number);

/**
 * @brief Same as MDE_calloc(), but allows the user to set a comment as metadata for the allocated memory block. If @a formatted_comment is NULL, no comment is added.
 * 
 * @param nmemb Number of objects.
 * @param size Size of each object.
 * @param file_name Name of file in which MDE_calloc_comment() was called.
 * @param line_number Number of line in @a file_name on which MDE_calloc_comment() was called.
 * @param formatted_comment Formatted string.
 * @param ... Arguments for @a formatted_comment.
 * @return void* 
 */
extern void* MDE_calloc_comment(size_t nmemb, size_t size, const char* file_name, int line_number, const char* formatted_comment, ...);

/**
 * @brief MDE extension of realloc(). Behaves like realloc(), but checks if @a size is 0, or reallocation failed.
 * 
 * @param ptr Pointer to the memory area to be reallocated.
 * @param size New size of the array in bytes.
 * @param file_name Name of file in which MDE_realloc() was called.
 * @param line_number Number of line in @a file_name on which MDE_realloc() was called.
 * @return void* 
 */
extern void* MDE_realloc(void* ptr, size_t size, const char* file_name, int line_number);

/**
 * @brief Same as MDE_realloc(), but allows the user to set a comment as metadata for the reallocated memory block. If @a formatted_comment is NULL, no comment is added. If the old memory block already had a comment, that comment is overwritten.
 * 
 * @param ptr Pointer to the memory area to be reallocated.
 * @param size New size of the array in bytes.
 * @param file_name Name of file in which MDE_realloc_comment() was called.
 * @param line_number Number of line in @a file_name on which MDE_realloc_comment() was called.
 * @param formatted_comment Formatted string.
 * @param ... Arguments for @a formatted_comment.
 * @return void* 
 */
extern void* MDE_realloc_comment(void* ptr, size_t size, const char* file_name, int line_number, const char* formatted_comment, ...);


/**
 * @brief MDE extension of free(). Behaves like free(), but checks if memory has never been allocated and, or has been deallocated before.
 * 
 * @param ptr Pointer to the memory to deallocate.
 * @param file_name Name of file in which MDE_free() was called.
 * @param line_number Number of line in @a file_name on which MDE_free() was called.
 */
extern void MDE_free(void* ptr, const char* file_name, int line_number);


/**
 * @brief Prints table of memory and metadata currently tracked by MDE.
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
#   define MDE_malloc(size)                                         MDE_malloc((size), (__FILE__), (__LINE__))
#   define MDE_calloc(nmemb, size)                                  MDE_calloc((nmemb), (size), (__FILE__), (__LINE__))
#   define MDE_realloc(ptr, size)                                   MDE_realloc((ptr), (size), (__FILE__), (__LINE__))

#   define MDE_malloc_comment(size, formatted_comment, ...)         MDE_malloc_comment((size), (__FILE__), (__LINE__), (formatted_comment), ##__VA_ARGS__)
#   define MDE_calloc_comment(nmemb, size, formatted_comment, ...)  MDE_calloc_comment((nmemb), (size), (__FILE__), (__LINE__), (formatted_comment), ##__VA_ARGS__)
#   define MDE_realloc_comment(ptr, size, formatted_comment, ...)   MDE_realloc_comment((ptr), (size), (__FILE__), (__LINE__), (formatted_comment), ##__VA_ARGS__)

#   define MDE_free(ptr)                                            MDE_free((ptr), (__FILE__), (__LINE__))

#   define MDE_tracker_destroy()                                    MDE_tracker_destroy((__FILE__), (__LINE__))
#endif /* MDE_NO_DEBUG_MEM */

#if defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG_MEM)
#   define malloc(size)                                             MDE_malloc((size))
#   define calloc(nmemb, size)                                      MDE_calloc((nmemb), (size))
#   define realloc(ptr, size)                                       MDE_realloc((ptr), (size))

#   define malloc_comment(size, formatted_comment, ...)             MDE_malloc_comment((size), (formatted_comment), ##__VA_ARGS__)
#   define calloc_comment(nmemb, size, formatted_comment, ...)      MDE_calloc_comment((nmemb), (size), (formatted_comment), ##__VA_ARGS__)
#   define realloc_comment(ptr, size, formatted_comment, ...)       MDE_realloc_comment((ptr), (size), (formatted_comment), ##__VA_ARGS__)

#   define free(ptr)                                                MDE_free((ptr))
#endif /* defined(MDE_DEBUG) && !defined(MDE_NO_DEBUG_MEM) */



#endif /* MDE_H */
