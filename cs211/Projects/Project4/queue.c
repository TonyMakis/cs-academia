#include "queue.h"

// ************* Queue Ops.' Definitions ****************

// This operation initialized a queue w/ default values
void initQueue(queue *q) {
    q->numGroups = 0;
    q->front = NULL;
    q->tail = NULL;
}

/* This operation is to add a new group to the end of the queue (enqueue)
 * This is to be used when the a and c commands are given as input.
 */
void addToList(queue *q, int size, char *name, boolean present) {
    // Create new group
    group *newGroup = malloc(sizeof(group));
    newGroup->size = size;
    newGroup->name = name;
    newGroup->isInRestaurant = present;
    // Add node to end of the queue
    if(q->numGroups == 0) {
        q->front = newGroup;
        q->tail = newGroup;
    } else {
        q->tail->next = newGroup;
        q->tail = newGroup;
    }
    newGroup->next = NULL;
    q->numGroups++;
}

/* This operation is to return a Boolean value indicating
 * whether a name already exists in the linked list.
 * This is to be used when the a, c, w and l commands are given as input.
 */
boolean doesNameExist(queue *q, char *name) {
    group *cur = q->front;
    while(cur != NULL) {
        if(strcmp(cur->name, name) == 0) return TRUE;
        cur = cur->next;
    }
    return FALSE;
}

/* This operation is to change the in-restaurant status when a call-ahead
 * group arrives at the restaurant. This operation will return a FALSE 
 * value if that group is already marked as being in the restaurant.
 * This is to be used when the w command is given as input.
 */
boolean updateStatus(queue *q, char *name) {
    group *cur = q->front;
    while(cur != NULL) {
        if(strcmp(cur->name, name) == 0) {
            if(!(cur->isInRestaurant)) {
                cur->isInRestaurant = YES;
                return TRUE;
            } else {
                return FALSE;
            }
        }
        cur = cur->next;
    }
    // No need for a return out here;
    // we are sure the name exists before calling this
}

// This operation is to remove a group (given a pointer to it) from the list
void removeFromList(queue *q, group *prev, group *cur) {
    if(cur == q->front) { // Front Group is being removed
        q->front = cur->next;
        cur->next = NULL;
    } else if(cur == q->tail) { // Tail Group is being removed
        q->tail = prev;
        prev->next = NULL;
    } else { // Other Group is being removed
        prev->next = cur->next;
        cur->next = NULL;
    }
}

/* This operation is to find the first in-restaurant group that can fit 
 * at a given table. This operation is to return the name of the group. This 
 * group is to be removed from the linked list.
 * This is to be used when the r command is given as input.
 */
char *retrieveAndRemove(queue *q, int tableSize) {
    group *cur = q->front;
    group *prev = NULL;
    char *name;
    while(cur != NULL) {
        if(cur->isInRestaurant && (cur->size <= tableSize)) {
            removeFromList(q, prev, cur);
            name = cur->name;
            free(cur);
            return name;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}

/* This operation is to return the number of groups waiting ahead of a group 
 * with a specific name. This is to be used when the l command is given as input.
 */
int countGroupsAhead(queue *q, char *name) {
    group *cur = q->front;
    int groupsAhead = 0;
    while(cur != NULL) {
        if(strcmp(cur->name, name) == 0) break;
        groupsAhead++;
        cur = cur->next;
    }
    return groupsAhead;
}

/* This operation traverses down the list until a specific group 
 * name is encountered. As each node is traversed, print out that node’s 
 * group size. This command is to be used when the l command is given.
 */
void displayGroupSizeAhead(queue *q, char *name) {
    group *cur = q->front;
    while(cur != NULL) {
        if(strcmp(cur->name, name) == 0) break;
        printf("%d ", cur->size);
        cur = cur->next;
    } 
}

/* This operation to traverse down the entire list from beginning to end. As each
 * node is traversed, print out that node’s group name, group size and in-restaurant
 * status. This command is to be used when the d command is given as input.
 */
void displayListInformation(queue *q) {
    printf("\n");
    group *cur = q->front;
    while(cur != NULL) {
        if(cur->next == NULL)
            printf("| %s: %d => %d |", cur->name, cur->size, cur->isInRestaurant);
        else 
            printf("| %s: %d => %d | -> ", cur->name, cur->size, cur->isInRestaurant);
        cur = cur->next;
    }
    printf("\n");
}

void freeQueue(queue *q) {
    group *cur = q->front;
    group *prev = NULL;

    while(cur != NULL) {
        if(prev != NULL) free(prev);
        free(cur->name);
        prev = cur;
        cur = cur->next;
    }
    
    free(prev); // Free that last Group Node
}
