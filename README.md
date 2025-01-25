# Memory Debugger Extraordinaire (MDE)

**Memory Debugger Extraordinaire (MDE)** is a powerful memory debugging library designed for C development. It integrates seamlessly with your project using its provided `CMakeLists.txt` file and functions as a standalone library.

---

## Features

MDE offers the following key features to enhance your debugging experience:

- **Memory Tracking**: Monitor allocated memory and receive detailed warning or error messages when issues occur.  
- **Metadata Support**: Attach comments as metadata to allocated memory blocks, enabling easy tracking of specific allocations.  
- **Program Crash on Errors**: Automatically crash the program when critical memory warnings or errors are detected, ensuring issues don't go unnoticed.  
- **Memory Table**: Print a detailed table of all currently allocated memory blocks along with their associated metadata.  

---

## Usage

To use the MDE versions of `malloc` and related functions, follow these steps:

1. **Include `MDE.h`:** Add `#include "MDE.h"` to your `.c` file.  
2. **Enable or Disable Debug Mode:**  
   - **Enable Debug Mode**: Uncomment the `#define MDE_DEBUG` macro in your code or configuration.  
   - **Disable Debug Mode**: Comment out the `#define MDE_DEBUG` macro.  

3. **Control Program Exit Behavior on Warnings or Errors:**  
   - To exit the program when warnings occur, uncomment the `#define MDE_EXIT_AT_WARNING` macro.  
   - To exit the program when errors occur, uncomment the `#define MDE_EXIT_AT_ERROR` macro.  
   - To disable this behavior, comment out the respective macros.

These options provide flexibility in configuring MDE to suit your debugging needs.

---

## Warning vs. Error

MDE differentiates between warnings and errors to help you identify the severity of issues:

- **Warnings**: Issued when unexpected behavior occurs, but the program can continue functioning. Examples include:  
  - Encountering implementation-defined behavior.  
  - `realloc` running out of memory.

- **Errors**: Issued for critical issues that result in undefined behavior or prevent MDE from functioning. Examples include:  
  - Memory required by MDE exceeds availability.  
  - Undefined behavior caused by unexpected circumstances.

> ⚠️ **Important Note**: If a warning or error occurs, MDE will stop tracking the affected memory pointer, as it cannot reliably predict how the program will handle the error.

---

## Future Goals

Looking ahead, the following features are planned for MDE:

- **Overlap Detection**: Identify overlapping memory regions to prevent hard-to-diagnose bugs.

---

MDE simplifies memory debugging, giving you more control and insight into your C programs.
