# Coding standard

## File structurizing

    Functions definitions that are related to the streams of Input and Output: workWithIO.c
    Functions definitions that are related to the main interface window/menu: workWithMenu.c
    Functions definitions that are related to the linked list: workWithList.c
    Functions declarations: main.h
    Globally used libraries: main.h
    User created data-types: main.h

## Code style

### Global variables

    Usage is limited/forbidden.
    If used, start the variable with a capital letter.

### Return values

    0 - the program has been terminated and completed its task successfully.
    -1 - there has been a non-treatable error. 

### Indentation and spacing

    One tab symbol for each nested block or braces
    A space between integers, operands, variables used and etc.
    An empty line between different coherent code segments.

### Usage of braces

    Should be used for all if, while, for, do statements, even if there is only one sentence inside of them.

        Correct:
            if(...)
            {
                ...
            }
                
        Wrong:
            if(...) {
                ...
            }

### Variables

    Only one variable per line.

### Variable naming

    Correct: toDoList
    Wrong: to_do_list

### Pointer variables

    Place the *close to the variable name not pointer type.

### Node data-type (and elements)

    struct Element;
        int data;
        struct Element *next;

### Commenting

    Unclear variables, tasks and statements are commented.

### Documentation

     Provide the documentation in a ReadMe.md file.        

### Goto

    Usage is strictly limited.

## Makefile usage

    make: create the main executable application file of the program

    make test: create an .exe test file

    make clear: delete all files in the folder created in the making of the executable application.

## Data files usage

    The data files should be located in a directory inside the working directory called "input".

## Test file usage

    The tests for functions should be provided in a file test.c in the working directory, using input marked with a word "test" as described in Data files usage.

## Using header file guards

    #ifndef NEWLIBRARYNAME_H
    #define NEWLIBRARYNAME_H
    
        /// header content

    #endif

## Macros

    No macros used.

## Embedded Assignments

    Should be avoided.
    Example:
        Wrong:
        d = (a = b + c) + r;
        Correct:
        a = b + c;
        d = a + r;
