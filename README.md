# get_next_line

A function that reads a text file line by line, regardless of the buffer size, implementing efficient memory management and handling multiple file descriptors simultaneously.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Function Prototype](#function-prototype)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Examples](#examples)
- [Bonus Features](#bonus-features)
- [Implementation Details](#implementation-details)
- [Testing](#testing)
- [Memory Management](#memory-management)
- [Edge Cases](#edge-cases)
- [Technical Specifications](#technical-specifications)
- [Author](#author)

## About

`get_next_line` is a C function that reads text files line by line, making it extremely useful for processing large files without loading them entirely into memory. This project teaches important concepts like static variables, dynamic memory allocation, file manipulation, and buffer management.

The function is designed to be memory efficient and can handle files of any size by reading them in chunks (defined by `BUFFER_SIZE`) while maintaining state between function calls using static variables.

## Features

- ✅ Reads files line by line efficiently
- ✅ Handles any buffer size (compile-time configurable)
- ✅ Works with files of any size
- ✅ **Bonus**: Supports multiple file descriptors simultaneously
- ✅ **Bonus**: Can handle up to 1024 file descriptors
- ✅ Proper memory management with no leaks
- ✅ Handles edge cases (empty files, single characters, large lines)
- ✅ Returns exactly one line per call
- ✅ Compatible with 42 Norm standards

## Installation

1. Clone or download the project files
2. Include the appropriate files in your project:

**For basic version:**
```bash
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

**For bonus version (multiple FDs):**
```bash
get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h
```

## Usage

Include the header file in your C program:

```c
#include "get_next_line.h"        // Basic version
// OR
#include "get_next_line_bonus.h"  // Bonus version
```

Compile with a defined buffer size:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_program.c
```

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: File descriptor to read from

### Return Value
- **Success**: A string containing the next line (including `\n` if present)
- **End of file**: `NULL`
- **Error**: `NULL`

## Project Structure

```
get_next_line/
├── get_next_line.c              # Main function (basic version)
├── get_next_line_utils.c        # Utility functions (basic version)
├── get_next_line.h              # Header file (basic version)
├── get_next_line_bonus.c        # Main function (bonus version)
├── get_next_line_utils_bonus.c  # Utility functions (bonus version)
├── get_next_line_bonus.h        # Header file (bonus version)
├── README.md                    # This file
└── gnlTester/                   # Test framework (if present)
    ├── Dockerfile
    ├── Makefile
    └── tests/
```

## Compilation

### Basic Compilation
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test_gnl
```

### Different Buffer Sizes
```bash
# Small buffer
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o test_gnl

# Large buffer
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c main.c -o test_gnl
```

### Bonus Version (Multiple FDs)
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o test_gnl_bonus
```

## Examples

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

### Multiple File Descriptors (Bonus)

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1, fd2;
    char *line1, *line2;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    
    // Read alternately from both files
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    
    while (line1 || line2)
    {
        if (line1)
        {
            printf("File1: %s", line1);
            free(line1);
            line1 = get_next_line(fd1);
        }
        if (line2)
        {
            printf("File2: %s", line2);
            free(line2);
            line2 = get_next_line(fd2);
        }
    }
    
    close(fd1);
    close(fd2);
    return (0);
}
```

## Bonus Features

The bonus version includes several advanced features:

### Multiple File Descriptor Support
- Can handle up to **1024 file descriptors** simultaneously
- Each file descriptor maintains its own reading state
- Uses static array: `static char *storage[MAX_FD]`

### Enhanced Error Handling
- Validates file descriptor range: `fd >= 0 && fd < MAX_FD`
- Proper cleanup when errors occur
- Memory safety for all file descriptors

### Usage Example
```c
// Open multiple files and read from them alternately
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
int fd3 = open("file3.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // Read line 1 from file1
char *line2 = get_next_line(fd2);  // Read line 1 from file2
char *line3 = get_next_line(fd3);  // Read line 1 from file3
char *line4 = get_next_line(fd1);  // Read line 2 from file1
```

## Implementation Details

### Core Algorithm

1. **Read Data**: Read chunks of `BUFFER_SIZE` bytes from the file
2. **Store Data**: Accumulate data in a static variable (storage)
3. **Extract Line**: Find the first newline and extract the line
4. **Update Storage**: Keep remaining data for the next call
5. **Return Line**: Return the extracted line to the caller

### Key Functions

| Function | Purpose |
|----------|---------|
| `get_next_line()` | Main function that orchestrates the reading process |
| `read_buffer()` | Reads data from file descriptor into storage |
| `ft_extract_line()` | Extracts one line from the accumulated storage |
| `ft_update_storage()` | Updates storage to remove the extracted line |
| `ft_join_and_free()` | Joins strings and frees memory efficiently |

### Utility Functions

| Function | Description |
|----------|-------------|
| `ft_strlen()` | Calculates string length |
| `ft_strjoin()` | Joins two strings |
| `ft_strchr()` | Finds character in string |
| `ft_calloc()` | Allocates and initializes memory |
| `ft_bzero()` | Sets memory to zero |

## Testing

### Test Files
Create test files with different characteristics:

```bash
# Empty file
touch empty.txt

# Single line without newline
echo -n "Single line without newline" > single_no_nl.txt

# Single line with newline
echo "Single line with newline" > single_with_nl.txt

# Multiple lines
printf "Line 1\nLine 2\nLine 3\n" > multiple_lines.txt

# Large line
python -c "print('x' * 10000)" > large_line.txt
```

### Basic Test Program
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int line_count = 0;
    
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    
    while ((line = get_next_line(fd)) != NULL)
    {
        line_count++;
        printf("Line %d: %s", line_count, line);
        if (line[strlen(line) - 1] != '\n')
            printf("\n");
        free(line);
    }
    
    printf("Total lines read: %d\n", line_count);
    close(fd);
    return (0);
}
```

## Memory Management

### Key Principles
- **Always free returned lines**: Each call to `get_next_line()` returns a malloc'd string
- **Static variable management**: The function manages its own internal storage
- **Error cleanup**: All memory is freed when errors occur
- **No memory leaks**: Proper cleanup when reaching end of file

### Memory Usage Pattern
```c
char *line;
while ((line = get_next_line(fd)) != NULL)
{
    // Use the line
    printf("%s", line);
    
    // ALWAYS free the line
    free(line);
}
// Static storage is automatically cleaned up
```

## Edge Cases

The implementation handles various edge cases:

### File Conditions
- ✅ Empty files
- ✅ Files with only newlines
- ✅ Files without final newline
- ✅ Very large lines (> BUFFER_SIZE)
- ✅ Files with mixed line lengths

### Buffer Sizes
- ✅ BUFFER_SIZE = 1 (character by character)
- ✅ BUFFER_SIZE = very large number
- ✅ BUFFER_SIZE = exact line length

### Error Conditions
- ✅ Invalid file descriptors (fd < 0)
- ✅ Closed file descriptors
- ✅ Permission denied
- ✅ Memory allocation failures

### Bonus Edge Cases
- ✅ File descriptor out of range (>= MAX_FD)
- ✅ Multiple file descriptors with different states
- ✅ Interleaved reading from multiple files

## Technical Specifications

### Constants
```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42        // Default buffer size
#endif

#ifndef MAX_FD                 // Bonus only
# define MAX_FD 1024          // Maximum file descriptors
#endif
```

### Constraints
- **No global variables** (except static variables in functions)
- **No libft allowed** (custom utility functions only)
- **Memory efficient** (no unnecessary allocations)
- **42 Norm compliant** (coding standards)

### Allowed Functions
- `read()`, `malloc()`, `free()`
- Standard library functions are **NOT** allowed

### Performance Characteristics
- **Time Complexity**: O(n) where n is the line length
- **Space Complexity**: O(BUFFER_SIZE + line_length)
- **Memory Usage**: Minimal, only stores current line and buffer

## Author

**Micampil** - micampil@student.42lisboa.com

Created as part of the 42 Lisboa curriculum.

---

*This project is part of the 42 school common core curriculum and follows the 42 Norm coding standards.*

## Additional Notes

### Why get_next_line?
This function is particularly useful for:
- **Log file processing**: Reading large log files line by line
- **Configuration files**: Parsing configuration files
- **Data processing**: Processing CSV or text data files
- **Memory efficiency**: Handling files larger than available memory

### Learning Objectives
- Understanding **static variables** and their persistence
- Mastering **dynamic memory allocation** and management
- Learning **file I/O operations** in C
- Implementing **buffer management** strategies
- Handling **multiple file descriptors** (bonus)

The `get_next_line` project is an excellent introduction to systems programming concepts and prepares students for more advanced projects involving file manipulation and memory management.
