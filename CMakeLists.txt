add_library(MDE
    src/MDE_calloc.c
    src/MDE_free.c
    src/MDE_malloc.c
    src/MDE_memory.c
    src/MDE_print.c
    src/MDE_realloc.c
    src/MDE_tracker.c
)

add_library(MDE_compiler_flags INTERFACE)
target_compile_features(MDE_compiler_flags INTERFACE c_variadic_macros)

target_link_libraries(MDE PRIVATE MDE_compiler_flags)

target_include_directories(MDE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
