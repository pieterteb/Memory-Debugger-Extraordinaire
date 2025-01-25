add_library(MDE
src/MDE_calloc.c
src/MDE_free.c
src/MDE_malloc.c
src/MDE_memory.c
src/MDE_print.c
src/MDE_realloc.c
src/MDE_tracker.c
)

target_include_directories(MDE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
