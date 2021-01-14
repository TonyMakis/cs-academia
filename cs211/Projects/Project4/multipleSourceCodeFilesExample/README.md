# Project 4: Restaurant Waiting List System

## An Example of Using Multiple Code Source Files

This directory is an example of how to compile a program with multiple source files.

### Files' Purposes

>Note: `max3a.c` and `max3b.c` just contain functions and a `#include` of `max3.h`.

The file `max3.h` contains the prototypes (or forward declarations) for all of the functions that are called from outside its source code file and any _globally_ needed information.

### Makefile Recipe

The makefile is a special file that helps in the compilation of the source code into the object files into the executable file. A makefile is executed by the use of the makecommand. The syntax of a makefile can be strange. I have always found that it is easiest to modify an existing makefile rather than trying to create one from scratch. The makefile will contain multiple rules. Each rule has the following syntax:

```Makefile
target: dependencyList
    commandLine
```

The multiple rules in the make file are separated by a blank line. Also note (this is __VERY IMPORTANT__) the commandLine must use a `TAB` for its indentation! An example of a rule is:

```Makefile
max3a.o: max3a.c max3.h
    gcc -c max3a.c
```

The _commandLine_ is `gcc-c max3a.c`, which will compile the source code file of `max3a.c` into the object code file of `max3a.o`.The target in the above example is the file `max3a.o`, which is also the name of the file created when the _commandLine_ is executed. This relationship is what causes makefiles to work.

The _dependencyList_ in the above example is the two files: `max3a.c` and `max3.h`, which are the files needed for the _commandLine_ to properly run. Again, this relationship is what causes makefiles to work.

The make command uses the timestamps of the files in the target and the _dependencyList_. If any file in the _dependencyList_ has a more recent timestamp than the target file, the _commandLine_ is executed. The idea is that if the user has recently changed either `max3a.c` or `max3.h`, then the object file `max3a.o` needs to be re-compiled. `Make` is designed to help the programmer keep track of what needs to be compiled next.

## How to Apply This to the Restaurant Program

Your program is to be written using at least three source code files. It must also have a makefile and a header file to help with the compilation of the program. All of the storage structure code (the linked list code) is to be in one source code file. The code in `proj4base.c` is to be separated into two different source code files.

The following functions from `proj4base.c` are to be in one source code file (these are the user interface functions):

- `main()`
- `clearToEoln()`
- `getNextNWSChar()`
- `getPosInt()`
- `getName()`
- `printCommands()`

The following functions from `proj4base.c` are to be in another source code file (these are the functions that interact with the linked list functions):

- `doAdd()`
- `doCallAhead()`
- `doWaiting()`
- `doRetrieve()`
- `doList()`
- `doDisplay()`

The third source code file is to have the code that you are writing that will perform the linked list implementation; the functions in this source code file will include the following functions plus any other you write to handle the linked list:

- `addToList()`
- `doesNameExist()`
- `updateStatus()`
- `retrieveAndRemove()`
- `countGroupsAhead()`
- `displayGroupSizeAhead()`
- `displayListInformation()`

You must also create a header file. The job of the header file is to contain the information so the source code files can talk to each other. The header file (`.h` file) should contain the function prototypes and any struct and/or typedef statements. Please review the `.h` file in the example below.

The makefile __MUST__ seperately compile each source code file into a `.o` file and separately link the `.o` files together into an executable file. Review the makefile in the example below to see how this is done. The command to create the `.o` file is:

```Shell
gcc –c program1.c
```

The command to link the files `program1.o`, `program2.o`, and `program3.o` into an executable file is:

```Shell
gcc program1.o program2.o program3.o
```

The above command will just name the executable file using the default name of `a.out`, most often the `–o` option is given to provide a specific name for the executable file:

```Shell
gcc program1.o program2.o program3.o –o program.exe
```
