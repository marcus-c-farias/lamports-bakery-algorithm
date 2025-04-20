# Tutorial: Creating and Using a Shared Library in C (Linux)

This tutorial outlines the steps to create a shared library from C source files and use it in a main program on a Linux system.

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

0.  **Optional**

    If you want to clone and ignore the file structure above.
    ```bash
    git clone https://github.com/marcus-c-farias/lamports-bakery-algorithm.git
    ```

1.  **Navigate to the Directory**

    Use the `cd` command to enter the directory containing your source files.

    ```bash
    cd lamports-bakery-algorithm/solution/
    ```

2.  **Compile Library Code to Object Code**

    Compile the library's C source file (`lamport_mutex.c`) into an object file (`lamport_mutex.o`). The `-fPIC` flag is crucial for shared libraries as it generates Position Independent Code.

    ```bash
    gcc -fPIC -c lamport_mutex.c -o lamport_mutex.o
    ```

    * `gcc`:  Invokes the GCC compiler.
    * `-fPIC`:  Enables Position Independent Code.
    * `-c`:  Performs compilation only (no linking).
    * `lamport_mutex.c`:  The C source file.
    * `-o lamport_mutex.o`:  The output object file.

3.  **Create the Shared Library**

    Create the shared library (`libLamport_mutex.so`) from the object file.

    ```bash
    gcc -shared lamport_mutex.o -o liblamport_mutex.so
    ```

    * `gcc`:  Invokes the GCC compiler.
    * `-shared`:  Creates a shared library.
    * `lamport_mutex.o`:  The object file.
    * `-o liblamport_mutex.so`:  The output shared library file.

4.  **Compile the Main Program and Link**

    Compile the main program (`main.c`) and link it with the created shared library.

    ```bash
    gcc main.c -L. -llamport_mutex -o program
    ```

    * `gcc`:  Invokes the GCC compiler.
    * `main.c`:  The main program's C source file.
    * `-L.`:  Specifies the directory to search for the library ('.' for the current directory).
    * `-llamport_mutex`:  Links with the library (GCC automatically adds the 'lib' prefix and '.so' extension).
    * `-o program`:  Specifies the output executable file name.

5.  **Execute the Program (with LD_LIBRARY_PATH)**

    Before running the executable, set the `LD_LIBRARY_PATH` environment variable to help the system locate the shared library at runtime.

    ```bash
    export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
    ```

    * `export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH`:  Sets the `LD_LIBRARY_PATH` variable, adding the current directory ('.') to the library search path.


6.  **Run the Program**

    ```bash
    ./program
    ```
    
    * `./program`:  Executes the compiled program.

Following these steps will compile your C code into a shared library and correctly link and run your main program.
