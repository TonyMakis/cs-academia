#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Added some colors for pretty printing!
// -> used as %s, injected into print strings
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KCYN  "\x1B[36m"

// Type/Function/Struct Definitions/Declarations

// Declaration of a boolen type, that can take the values in braces
typedef enum {FALSE = 0, TRUE = 1, NO = 0, YES = 1} boolean;

// 1. ************************ queue.c ************************************************

// A linked list implementation

// Group: has name, group size, in-restaurant status and points to next Group
//  -> this is a 'node' struct in essence that composes the queue struct
typedef struct group {
    int size;
    char *name;
    boolean isInRestaurant;
    struct group *next;
} group;

// Queue: tracks total number of groups in queue, as well as the leading group
typedef struct queue {
    int numGroups;
    boolean debugMode;
    group *front;
    group *tail;
} queue;

void initQueue(queue *q, boolean debug_mode);
void addToList(queue *q, int size, char *name, boolean present);
boolean doesNameExist(queue *q, char *name);
boolean updateStatus(queue *q, char *name);
void removeFromList(queue *q, group *prev, group *cur);
char *retrieveAndRemove(queue *q, int tableSize);
int countGroupsAhead(queue *q, char *name);
void displayGroupSizeAhead(queue *q, char *name);
void displayListInformation(queue *q);
void freeQueue(queue *q);

// 2. ********************** restaurant.c **********************
void doAdd(queue *q);
void doCallAhead(queue *q);
void doWaiting(queue *q);
void doRetrieve(queue *q);
void doList(queue *q);
void doDisplay(queue *q);

// 3. ************************ input.c ************************
int main(int argc, char **argv);
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();
