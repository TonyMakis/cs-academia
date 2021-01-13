#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Added some colors for pretty printing!
// -> used as %s, injected into print strings
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KCYN  "\x1B[36m"

// ************* Struct Definitions ****************

// Node: contains coordinates corresponding to a maze position
//       and points to next Node
typedef struct node {
    int x;
    int y;
    struct node *prev;
} node;

// Stack: tracks total number of nodes on stack, as well as the top node
typedef struct stackStruct {
    int numNodes;
    node *top;
} stack;

// Maze: keeps track of the maze and its metadata
typedef struct mazeStruct {
    char **arr;
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} maze;

// ************** Command Format Checking *****************

int cmdUsageMsg(char *cmd) {
    fprintf( stderr, "%s\n\tUsage: %s <input file name> [OPTIONALS]\n\n", KYEL, cmd );
    fprintf( stderr, "\tOPTIONAL ARGUMENTS (Can occur anywhere in command):\n\n");
    fprintf( stderr, "\t\t-d, \temit debugging messages\n%s", KNRM);
    exit(-1);
}

void checkFile(char *fileName) {
    FILE *src;
    if (( src = fopen( fileName, "r" )) == NULL ) { // Try opening file
        fprintf( stderr, "%s\n\tCan't open input file: %s%s\n%s", 
                 KYEL, KRED, fileName, KNRM);
        exit(-1);
    }
    fclose(src);
}

/* Verify the proper number of command line arguments were given and are valid 
 *
 * @param argc: number of cmd line args entered
 * @param argv: points to the set of strings entered on cmd line
 * @param debug_mode: whether to set debug mode to true or false (0/1)
 * @param fileNameIndex: the index in @argv where the filename occurs
 */

void checkCmdArgs(int argc, char **argv, int *debug_mode, int *fileNameIndex) {
    // By default, debug mode is off and fileName is usually the first arg in command
    *debug_mode = 0, *fileNameIndex = 1;
    switch(argc) {
        case 2: // No optional args given, just filename!
            checkFile(argv[1]);
            break;
        case 3: // Either argv[1] or argv[2] is a -d optional arg!
            if(strcmp(argv[2], "-d") == 0) {
                checkFile(argv[1]);
                *debug_mode = 1;
                *fileNameIndex = 1;
            } else if(strcmp(argv[1], "-d") == 0) {
                checkFile(argv[2]);
                *debug_mode = 1;
                *fileNameIndex = 2;
            } else {
                cmdUsageMsg(argv[0]);
            }
            break;
        default: // Not enough or too many args supplied!
            cmdUsageMsg(argv[0]);
    }
}

// ************** Input Coordinate Validation *****************

int coordinatesAreOverZero(int row, int col) {
    return row > 0 && col > 0;
}

int coordinatesAreInRange(int row, int col, int rowMax, int colMax) {
    return row <= rowMax && col <= colMax;
}

int willBlockTheStartOrEnd(int row, int col,
                        int startRow, int startCol,
                        int endRow, int endCol) {
    return (row == startRow && col == startCol) || (row == endRow && col == endCol);
}

int mazeMetadataIsValid(maze *m) {
    return coordinatesAreOverZero(m->xsize, m->ysize) &&
           coordinatesAreOverZero(m->xstart, m->ystart) &&
           coordinatesAreOverZero(m->xend, m->yend);
}

void checkMazeSetup(FILE *src, maze *m, char *file) {
    // Ensure three valid lines were found or force an error-exit
    if(!mazeMetadataIsValid(m)) {
        fprintf(stderr, "%s\n\t%s cannot be made into a maze! ", KYEL, file);
        fprintf(stderr, "unable to find size, start, and/or ");
        fprintf(stderr, "end coordinates that are valid!\n%s", KNRM);
        fclose(src);
        exit(-1);
    }
}
// *************** Reading Input File / Building Maze *****************

void getMazeSize(FILE *src, maze *m) {
    int xpos, ypos;
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF) {
        if(coordinatesAreOverZero(xpos, ypos)) {
            m->xsize = xpos;
            m->ysize = ypos;
            break;
        }
    }
}

void getMazeStart(FILE *src, maze *m) {
    int xpos, ypos;
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF) {
        if(coordinatesAreOverZero(xpos, ypos) && 
           coordinatesAreInRange(xpos, ypos, m->xsize, m->ysize)) {
            m->xstart = xpos;
            m->ystart = ypos;
            break;
        }
    }
}

void getMazeEnd(FILE *src, maze *m) {
    int xpos, ypos;
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF) {
        if(coordinatesAreOverZero(xpos, ypos) && 
           coordinatesAreInRange(xpos, ypos, m->xsize, m->ysize)) {
            m->xend = xpos;
            m->yend = ypos;
            break;
        }
    }
}

void initMaze(maze *m) {
    int i,j;
    // Dynamically alloate 2D array for maze
    m->arr = malloc(sizeof(char *) * (m->xsize + 2));
    for(int i = 0; i < m->xsize + 2; i++) {
        m->arr[i] = malloc(sizeof(char) * (m->ysize + 2));
    }

    // Initialize maze (to empty with '.'s)
    for (i = 0; i < m->xsize + 2; i++)
        for (j = 0; j < m->ysize + 2; j++)
            m->arr[i][j] = '.';

    // Mark the borders of the maze with '*'s
    for (i = 0; i < m->xsize + 2; i++) {
        m->arr[i][0] = '*';
        m->arr[i][m->ysize+1] = '*';
    }
    for (i=0; i < m->ysize + 2; i++) {
        m->arr[0][i] = '*';
        m->arr[m->xsize+1][i] = '*';
    }

    // Mark the starting and ending positions in the maze
    m->arr[m->xstart][m->ystart] = 's';
    m->arr[m->xend][m->yend] = 'e';
}

/* mark the blocked positions in the maze with *'s */
void getAndSetMazeBlockers(FILE *src, maze *m) {
    int xpos, ypos;
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF) {
        if(coordinatesAreOverZero(xpos, ypos) &&
           coordinatesAreInRange(xpos, ypos, m->xsize, m->ysize) &&
           !willBlockTheStartOrEnd(xpos, ypos, m->xstart, m->ystart, m->xend, m->yend))
            m->arr[xpos][ypos] = '*';
    }
}

void printMaze(maze *m) {
    printf("\n\t***MAZE INFO***\n\t-----------------\n");
    printf("\t SIZE: %d, %d\n\tSTART: %d, %d\n\t  END: %d, %d\n\n%s", 
           m->xsize, m->ysize, m->xstart, m->ystart, m->xend, m->yend, KCYN);
    int i,j;
    for (i = 0; i < m->xsize + 2; i++) {
        printf("\t");
        for (j = 0; j < m->ysize + 2; j++)
            printf("%c", m->arr[i][j]);
        printf("\n");
    }
    printf("\n%s", KNRM);
}

// *************** Stack Ops.' Definitions ****************

void initStack(stack *s) {
    s->numNodes = 0;
    s->top = NULL;
}

int stackIsEmpty(stack *s) { return s->numNodes == 0; }


void push(stack *s, int x, int y, int debugMode) {
    // Create new node
    node* newNode = malloc(sizeof(node));
    newNode->x = x;
    newNode->y = y;
    newNode->prev = s->top;
    // Add node to top of stack
    s->top = newNode;
    s->numNodes++;
    if(debugMode) printf("\t*** (%d, %d) was %spushed%s onto the stack!\n", x, y, KGRN, KNRM);
}

// Pop off the top node on the stack, and return it
// USER OF THIS FUNCTION NEEDS TO REMEMBER TO FREE POPPED NODE
node* pop(stack *s, int debugMode) {
    // track the node to pop
    node *popped = s->top;
    // pop the node
    s->top = s->top->prev;
    popped->prev = NULL;
    s->numNodes--;
    // return tracked, popped node
    if(debugMode) printf("\t*** (%d, %d) was %spopped%s off of the stack!\n", 
                         popped->x, popped->y, KRED, KNRM);
    return popped;
}

void printStack(stack *s) {
    printf("\n THE STACK \n------------\n|  TOP\n------------\n");
    node *cur = s->top;
    while(cur != NULL) {
        printf("| (%d, %d) \n", cur->x, cur->y);
        cur = cur->prev;
    }
    printf("------------\n| BOTTOM\n------------\n# NODES => %d\n", s->numNodes);
}

// Free dynamically allocated stack nodes; pop each and free it
void freeStack(stack *s, int debugMode) { 
    if(!stackIsEmpty(s)) {
        while(s->top != NULL) free(pop(s, debugMode));        
    }
}

// *************** DFS Implementation ****************

// Checks top of stack node's neightbors for unvisited nodes
// If there is an unvisited node, set x and y, and return true, unvisited found
// If there are no unvisited nodes around, don't set x and y, just return false
int searchNeighbors(maze *m, stack *s, int *x, int *y, char searchChar) {
    if(m->arr[(s->top->x) - 1][s->top->y] == searchChar) { // Check up
        *x = (s->top->x) - 1;
        *y = s->top->y;
        return 1;
    } else if(m->arr[s->top->x][(s->top->y) + 1] == searchChar) { // Check right
        *x = s->top->x;
        *y = (s->top->y) + 1;
        return 1;
    } else if(m->arr[(s->top->x) + 1][s->top->y] == searchChar) { // Check down
        *x = (s->top->x) + 1;
        *y = s->top->y;
        return 1;
    } else if(m->arr[s->top->x][(s->top->y) - 1] == searchChar) { // Check left
        *x = s->top->x;
        *y = (s->top->y) - 1;
        return 1;
    }
    return 0;
}

int attemptSolvingMaze(maze *m, stack *s, int debugMode) {
    int foundEnd = 0;
    // Unvisited locations already each marked with a period
    // First, push start position onto stack
    push(s, m->xstart, m->ystart, debugMode);
    // Now mark start position as visited in maze
    int hasNotBeenVisited, x, y, endFound = 0;
    m->arr[m->xstart][m->ystart] = 'V';
    while(!stackIsEmpty(s)) {
        // Check for end amongst neighbors
        if(searchNeighbors(m, s, &x, &y, 'e')) {
            push(s, x, y, debugMode);
            break;
        }
        // Check for unvisited neigbors
        if(searchNeighbors(m, s, &x, &y, '.')) {
            push(s, x, y, debugMode);
            m->arr[s->top->x][s->top->y] = 'V';
        } else // No neigbors are end / all are visited already
            free(pop(s, debugMode)); // We don't need to look at the node, free it right away
    }
    // Stack is empty here (1) => maze has no solution, return 0
    // Stack is not empty here (0) => maze has a solution, return 1
    return !stackIsEmpty(s);
}

void printSolutionPath(stack *s) {
    stack reverseOrder;
    initStack(&reverseOrder);
    node *cur = s->top;
    while(cur != NULL) {
        push(&reverseOrder, cur->x, cur->y, 0); // Never debug output here
        cur = cur->prev;
    }
    cur = reverseOrder.top;
    printf("\nThe solution path:\n\n");
    while(cur != NULL) {
        printf("(%d, %d) ", cur->x, cur->y);
        cur = cur->prev;
    }
    printf("\n");
    freeStack(&reverseOrder, 0); // Never debug output here
}

int main (int argc, char **argv) {
    int debug_mode, fileNameIndex;
    // If cmd is bad, program lets user know and dies; otherwise it continues past
    checkCmdArgs(argc, argv, &debug_mode, &fileNameIndex);
    
    // If we have made it here, the file is found and good for opening
    FILE *src = fopen( argv[fileNameIndex], "r" );

    // Maze setup variables; by default, set all maze metadata to 0
    maze m;
    m.xsize = 0, m.ysize = 0,
    m.xstart = 0, m.ystart = 0,
    m.xend = 0, m.yend = 0;

    getMazeSize(src, &m);
    getMazeStart(src, &m);
    getMazeEnd(src, &m);

    checkMazeSetup(src, &m, argv[fileNameIndex]);

    initMaze(&m);
    getAndSetMazeBlockers(src, &m);
    printMaze(&m);

    // For all intents and purposes, s.top indicates the
    // "head/top" of the linked list of Nodes (a.k.a a Stack)
    stack s;
    initStack(&s);

    int mazeSolved = attemptSolvingMaze(&m, &s, debug_mode);

    mazeSolved ? printSolutionPath(&s) : printf("\nThis maze has no solution!\n");

    // Free maze dynamic memory from the heap
    for(int i = 0; i < m.xsize + 2; i++) free(m.arr[i]);
    free(m.arr);

    freeStack(&s, debug_mode);

    fclose(src);
}
