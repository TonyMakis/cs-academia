# Project 3: Maze Solving

## Background Info

Write a C program that will find its way through a maze using the depth-first search algorithm. This program takes input from a file where the filename is specified in the command line arguments.

## Project Guide

```Input
10 20
1 1
10 20
5 1
4 2
3 3
1 10
2 9
3 8
4 7
5 6
6 5
7 4
8 3
```

After processing input (when it is valid) one should achieve a maze:

```Maze
size: 10, 20; start: 1, 1; end: 10, 20

**********************
*s........*..........*
*........*...........*
*..*....*............*
*.*....*.............*
**....*..............*
*....*...............*
*...*................*
*..*.................*
*....................*
*...................e*
**********************
```

>The blocked positions and the edges of the above maze are filled in with *'s. The start position is filled in with an 's'. The end position in filled in with an 'e'. The other positions are filled in with periods. The maze is a 2D-array

The algorithm you are to use to find a path through the maze is a _Depth First Search_ (DFS). You __MUST__ use the following form of a Depth First Search, employing the Stack you made previously in Project 2:

- Mark all unblocked positions in the maze as __UNVISITED__
- Push the start position's coordinates on the stack
- Mark the start position as visited
- `While`(stack is not empty and end has not been found)
  - `If` the coordinate at the Top of the Stack is the end position
    - Then end has been found
  - `If` the coordinate at the Top of the Stack has an unvisited (and unblocked) neighbor
    - Push the coordinates of the unvisited neighbor on the stack
    - Mark the unvisited neighbor as visited
  - `Else`
    - Pop the coordinate at the Top of the Stack
- `If` the stack is empty
  - The maze has no solution
- `Else`
  - The items on the stack contain the coordinates of the solution from the end of the maze to the start of the maze

>When referring to neighbors, those positions will be the ones above, below, left or right of the current position (not diagonal). So for position `(x, y)` its neighbors are at:
>
>- `(x+1, y)`
>- `(x-1, y)`
>- `(x, y+1)`
>- `(x, y-1)`
>

### Input

You may assume that the input will always have two integer values per line; however, the values may be out of range. If an invalid value is given on an input line, print a descriptive error message to __STANDARD ERROR__, ignore those two input values and continue processing input using the next line of input. Any value of zero or less is invalid in this program. For a coordinate value in the maze, valid value range from 1 to the maximum row size or column size. Also, the starting and ending positions of the maze must never be blocked. Since errors may exist:

- The first valid line gives the size of the 2-D maze (the number of rows given by the first number, then the number of columns given by the second number), valid values are >= 1
- The second valid line gives the coordinates of the starting position in the maze
- The third valid line gives the coordinates of the ending position in the maze
- The remaining valid lines in the file give the coordinates of blocked positions in the maze

If the file ends before getting 3 valid lines of input, print out an error message to __STANDARD ERROR__ and quit the program.

Examples of input files:
>The coordinates are given with the row listed first and the column listed second.
>A maze of N x M has rows numbered from 1 to N and columns numbered from 1 to M.

```Totally Valid Input
// Example 1
10 20
1 1
10 20
5 1
4 2
3 3
1 10
2 9
3 8
4 7
5 6
6 5
7 4
8 3
```

```Input with Invalids
// Example 2
10 0    => Invalid: Maze sizes must be greater than 0
15 7    => Maze becomes size 15 x 7
10 20   => Invalid: column 20 is outside range from 1 to 7
5 1     => Starting position is at position 5, 1
24 2    => Invalid: row 24 is outside of range from 1 to 15
3 3     => Ending position is at position 3, 3
1 10    => Invalid: column 10 is outside range from 1 to 7
2 9     => Invalid: column 9 is outside range from 1 to 7
3 8     => Invalid: column 8 is outside range from 1 to 7
4 7
5 6
5 1     => Invalid: attempting to block starting position
6 5
7 4
```

### Running Executable & Arguments

#### Input Files

If the command line arguments do not contain a valid filename, you should print an error message to __STANDARD ERROR__ and quit the program. This could be because there was not a name given or the name given did not match that of a valid file. If the command line arguments contains multiple names, we leave it up to you to come up with a “good solution”. Ideas on such a “good solution” could be:

- Use one of the names as the input file and proceed(pick which name makes most sense to use).
- Give an error message stating that too many names were given and quit.
- Run the program to solve the maze given with each filename.

#### Debug Flag

Your program must be able to take one optional command line argument, the `-d` flag. When this flag is given, your program is to run in __debug__ mode. When in this mode, your program is to display the coordinates of the maze positions as they are pushed onto the stack and popped off the stack if the Top of Stack coordinate does not have an unvisited (and unblocked) neighbor.

When the flag is not given, this debugging information should not be displayed. Since the input file for the maze also comes from the command line arguments, you may not assume which order in which the command line arguments are given. Thus the command line arguments may be given as:

- `./a.out  mazeInput.txt`
- `./a.out  mazeInput.txt  -d`
- `./a.out  -d  mazeInput.txt`

One simple way to set up a __debugging__ mode is to use a boolean variable which is set to true when debugging mode is turned on but false otherwise. Then using a simple if statement controls whether information should be outputor not.

```C
if ( debugMode == TRUE )
    printf (" Debugging Information \n");
```

### Output

Your program is to first output the size of the maze, the start and ending coordinates and an ASCII drawing of the maze.

Once the maze solving algorithm is run, you must then print out a message stating either:

- the maze has no solution _or_
- listing the coordinates of the locations of the path in the maze from the start of the maze to the end of the maze that was found by the algorithm. Note this means printing out the contents of the stack in reverse order.

## Project Structure

This is to be developed in one stage, procedurally. There are 5 files being provided to us:

- maze.c => starter code to help prioritize implmentation
- mazeData`N`.txt => where `N` is any number in `{1,2,3,4}`; there are four different maze input files to try out with the program!

## Restrictions for this Project

Your DFS algorithm __may not__ use recursion; follow the guidelines of the implmentation provided. You are __NOT__ allowed to use this since you are __required__ to use your own linked list stack from Project 2.

### Using the Starter Code (maze.c)

The `maze.c` program uses a static sized 2-D array; however, your program __MUST__ use a dynamic 2-D array sized to reflect the maze size given in the input file. You must alsodynamically deallocate this array at the end of your program. The `maze.c` program also does not do any error checking for invalid input, your program __MUST__ check for invalid input.

### More on Stack Implementation

The stack __MUST__ use a linked list of coordinate values. The head of the linked list __MUST NOT__ be global.  It must be declared as a local variable in `main()` or some other function. You may create a structure to contain the head of the stack if you desire but again the initial instance of the structure must be a local variable. The code for each stack operation __MUST__ be done in its own function where the head is passed in as a parameter.

## My Solution in Action

![Project 3 in Action!](./runningProject3.gif)

> I have a `Makefile` for quicker compilation, and then we run the executable (v1). `Makefile` is written to support general compilation of most `.c` files, so I will reuse it throughout projects, making updates to it ocassionally.
