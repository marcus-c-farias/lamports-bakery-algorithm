# Tutorial: Running lamports bakery algorithm

This tutorial outlines the steps to how to run the program.

## Prerequisites

* Ensure you have GCC (GNU Compiler Collection) installed.
* Organize your C source files (.c) and header files (.h) in a dedicated directory.

## File Structure Example

For this tutorial, assume the following file structure:

```
/Solution/
├── main.c             # Main program using the library
├── lamport_mutex.c    # Library implementation
└── lamport_mutex.h    # Library header file
```

## Steps

0.  **Clone the project**

    ```bash
    git clone https://github.com/marcus-c-farias/lamports-bakery-algorithm.git
    ```

1.  **Navigate to the Directory**

    Use the `cd` command to enter the directory containing your source files.

    ```bash
    cd lamports-bakery-algorithm/solution/
    ```

2.  **Run makefile**

    The makefile is already config to compile your C code into a shared library and correctly link and run your main program, after that it cleans. If you want to run step by step, run individual commands from makefile.

    ```bash
    make
    ```
