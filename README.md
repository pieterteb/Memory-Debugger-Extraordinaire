# Memory Debugger Extraordinaire
Memory Debugger Extraordinaire (MDE), is a memory debugging library for C development.

MDE comes with a CMakeLists.txt file that can be easily linked to your main project as a library.

Current Features:
- Track allocated memory and get detailed warning/error messages if an error occurs.
- Add comments to allocated memory as metadata. Useful if you want to track a specific memory block.
- Crash a running program if memory warnings/errors occur.
- Print a table containing all currently allocated memory addresses with their corresponding metadata.

A warning is given if something unexpected happens, but the program can still function normally afterwards. For example, if implementation defined behaviour is encountered or if realloc runs out of memory.

An error is given if something unexpected happens which causes undefined behaviour, or if MDE is unable to function properly. For example, if MDE needs more memory than is available.

If a warning or error occurs, MDE will not attempt to track the newly created pointer since it cannot always know how the program itself dealt with the error.

Future goals:
- Detect overlapping memory when required.
