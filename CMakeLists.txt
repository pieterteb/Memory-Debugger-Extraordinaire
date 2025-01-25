add_library(MDE
            src/MDE_alloced.c
            src/MDE_calloc.c
            src/MDE_free.c
            src/MDE_malloc.c
            src/MDE_print.c
            src/MDE_realloc.c
)

target_compile_features(MDE PRIVATE c_std_90)
target_include_directories(MDE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
